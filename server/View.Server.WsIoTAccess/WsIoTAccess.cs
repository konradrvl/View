using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Authentication;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Fleck;
using Microsoft.Extensions.Configuration;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using View.Server.Shared.IoTAccess;
using View.Server.WsIoTAccess.Messages;
using View.Server.WsIoTAccess.Messages.Parameters;

namespace View.Server.WsIoTAccess
{
    public class WsIoTAccess : IIoTAccess
    {
        private readonly IConfiguration _configuration;

        private const int HeartbeatTime = 4000;

        private readonly Dictionary<IWebSocketConnection, int> _wsToRoom = new Dictionary<IWebSocketConnection, int>();
        private readonly Dictionary<int, IWebSocketConnection> _roomToWs = new Dictionary<int, IWebSocketConnection>();

        private readonly Dictionary<string, IWebSocketConnection> _connections = new Dictionary<string, IWebSocketConnection>();

        private readonly HashSet<IWebSocketConnection> _validConnections = new HashSet<IWebSocketConnection>();
        
        private WebSocketServer _webSocketServer;

        private readonly object _lockGuard = new object();

        public WsIoTAccess(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        public event WsIotDelegates.IoTDeviceLoginRequestedDelegate IoTDeviceLoginRequested;
        public event WsIotDelegates.PersonCountChangedDelegate PersonCountChanged;
        public event WsIotDelegates.RoomInvalidatedDelegate RoomInvalidated;

        public void Start()
        {
            var wsUrl = _configuration.GetSection("detectorApi").Value;
            _webSocketServer = new WebSocketServer(wsUrl);

            _webSocketServer.Start(socket =>
            {
                socket.OnClose = () => OnClosed(socket);
                socket.OnError = e => OnClosed(socket);
                socket.OnMessage = message => OnMessage(socket, message);
                SendHeartbeat(socket);
            });
        }

        private void SendHeartbeat(IWebSocketConnection socket)
        {
            Task.Run(async () =>
            {
                while (socket.IsAvailable)
                {
                    bool pong = false;
                    await socket.SendPing(Encoding.UTF8.GetBytes("VIEW_PING"));
                    socket.OnPong += b => pong = true;
                    Thread.Sleep(HeartbeatTime);
                    if (!pong)
                    {
                        socket.Close();
                    }
                }
            });
        }

        public void Stop()
        {
            _webSocketServer?.Dispose();
        }

        public void SetInvalid(string iotDeviceId)
        {
            lock (_lockGuard)
            {
                if (_connections.ContainsKey(iotDeviceId))
                {
                    _connections[iotDeviceId].Send("LOGIN_INVALID");
                    _connections[iotDeviceId].Close();
                } 
            }
        }

        public void SetValid(string iotDeviceId)
        {
            lock (_lockGuard)
            {
                if (_connections.ContainsKey(iotDeviceId))
                {
                    var ws = _connections[iotDeviceId];
                    _validConnections.Add(ws);
                    SentLoginSucess(ws);
                }
            }
        }

        public void SetRoom(string iotDeviceId, int roomId)
        {
            lock (_lockGuard)
            {
                if(_connections.TryGetValue(iotDeviceId, out var ws))
                {
                    if (_validConnections.Contains(ws))
                    {
                        if (_wsToRoom.TryGetValue(ws, out var oldRoomId))
                        {
                            _roomToWs.Remove(oldRoomId);
                        }
                    
                        _wsToRoom[ws] = roomId;
                        _roomToWs[roomId] = ws;
                
                        RequestCurrentValue(ws);
                    }
                } 
            }
        }

        public void DeleteRoom(int roomId)
        {
            lock (_lockGuard)
            {
                if (_roomToWs.TryGetValue(roomId, out var ws))
                {
                    _roomToWs.Remove(roomId);
                    _wsToRoom.Remove(ws);
                }
            }
        }
        
        public void RequestCurrentValue(int roomId)
        {
            lock (_lockGuard)
            {
                if (_roomToWs.ContainsKey(roomId))
                {
                    RequestCurrentValue(_roomToWs[roomId]);
                }
            }
        }

        private void RequestCurrentValue(IWebSocketConnection webSocket)
        {
            webSocket.Send("REQUEST");
        }

        private void SentLoginSucess(IWebSocketConnection webSocket)
        {
            webSocket.Send("LOGIN_SUCCESS");
        }
        
        private void OnClosed(IWebSocketConnection webSocket)
        {
            lock (_lockGuard)
            {
                _validConnections.Remove(webSocket);

                if (_connections.ContainsValue(webSocket))
                {
                    var entry = _connections.First(x => x.Value == webSocket);
                    _connections.Remove(entry.Key);
                }

                if (_wsToRoom.ContainsKey(webSocket))
                {
                    var roomId = _wsToRoom[webSocket];
                
                    _wsToRoom.Remove(webSocket);
                    _roomToWs.Remove(roomId);
                
                    RoomInvalidated?.Invoke(roomId);
                }
            }
        }

        private void OnMessage(IWebSocketConnection webSocket, string message)
        {
            try
            {
                var messageType = GetMessageType(message);

                switch (messageType)
                {
                    case MessageType.LoginIoTDevice:
                        OnLogin(webSocket, message);
                        break;
                    case MessageType.PersonCountChanged:
                        OnPersonCountChanged(webSocket, message);
                        break;
                    default:
                        webSocket.Close();
                        break;
                }
            }
            catch (JsonReaderException)
            {
                webSocket.Close();
            }
            catch (AuthenticationException)
            {
                webSocket.Close();
            }
            catch (InvalidCastException)
            {
                webSocket.Close();
            }
        }

        private void OnLogin(IWebSocketConnection webSocket, string message)
        {
            var obj = GetIoTMessage<LoginIoTDeviceParameters>(message);

            if (obj.Parameters == null || _connections.ContainsKey(obj.Parameters.Id))
            {
                throw new AuthenticationException();
            }

            lock (_lockGuard)
            {
                _connections.Add(obj.Parameters.Id, webSocket);
            }

            IoTDeviceLoginRequested?.Invoke(obj.Parameters.Id);
        }

        private void OnPersonCountChanged(IWebSocketConnection webSocket, string message)
        {
            var obj = GetIoTMessage<PersonCountChangedParameters>(message);

            lock (_lockGuard)
            {
                if (!_validConnections.Contains(webSocket))
                {
                    throw new AuthenticationException();
                }
            }

            if (_wsToRoom.TryGetValue(webSocket, out var roomId))
            {
                PersonCountChanged?.Invoke(roomId, obj.Parameters.PersonCount, obj.Parameters.TimeStamp);
            }
        }

        private MessageType GetMessageType(string message)
        {
            var jsonObj = JObject.Parse(message);

            if (jsonObj.TryGetValue("type", out var jsonType))
            {
                var value = jsonType.Value<int>();
                return (MessageType) value;
            }

            throw new JsonReaderException("Invalid parameter");
        }

        private IoTMessage<T> GetIoTMessage<T>(string message)
        {
            return JsonConvert.DeserializeObject<IoTMessage<T>>(message);
        }
        
    }
}