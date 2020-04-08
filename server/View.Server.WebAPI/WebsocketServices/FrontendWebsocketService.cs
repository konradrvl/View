using System.Collections.Generic;
using System.Net.WebSockets;
using System.Security.Authentication;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using View.Server.Service.Stores;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.Services;

namespace View.Server.WebAPI.WebsocketServices
{
    public class FrontendWebsocketService
    {

        private readonly Dictionary<int, HashSet<WebSocket>> _roomWebsockets = new Dictionary<int, HashSet<WebSocket>>();

        private readonly OcupationServiceStore _ocupationServiceStore;
        
        private readonly IUserValidationService _userValidationService;

        public FrontendWebsocketService(OcupationServiceStore ocupationServiceStore, IUserValidationService userValidationService)
        {
            _ocupationServiceStore = ocupationServiceStore;
            _userValidationService = userValidationService;

            ocupationServiceStore.PersonCountChanged += OnDataChanged;
        }

        public async Task Start(WebSocket webSocket, User user)
        {
            while (true)
            {
                var erg = await WebsocketHelper.ReadString(webSocket);

                if (erg.WebSocketCloseStatus != null)
                {
                    OnClosed(webSocket);
                    break;
                }

                OnMessage(webSocket, erg.Text, user);
            }
        }

        private void OnClosed(WebSocket webSocket)
        {
            lock (_roomWebsockets)
            {
                foreach (var webSockets in _roomWebsockets.Values)
                {
                    webSockets.Remove(webSocket);
                }
            }
        }

        private async void OnMessage(WebSocket webSocket, string message, User user)
        {
            try
            {
                var roomIds = JsonConvert.DeserializeObject<int[]>(message);
                HandleNewRoomRegistration(webSocket, roomIds, user);
            }
            catch (JsonReaderException)
            {
                await webSocket.CloseAsync(WebSocketCloseStatus.PolicyViolation, "Got illegal message. Expected roomIds", CancellationToken.None);
            }
        }

        private async void HandleNewRoomRegistration(WebSocket webSocket, IEnumerable<int> roomIds, User user)
        {
            try
            {
                foreach (var roomId in roomIds)
                {
                    await _userValidationService.ValidateUserByRoomId(user, roomId);

                    lock (_roomWebsockets)
                    {
                        if (!_roomWebsockets.ContainsKey(roomId))
                        {
                            _roomWebsockets[roomId] = new HashSet<WebSocket>();
                        }

                        _roomWebsockets[roomId].Add(webSocket);

                        var currentPersonCount = _ocupationServiceStore.GetCurrentPersonCount(roomId);
                        SendPersonCount(webSocket, roomId, currentPersonCount);
                    }
                }
            }
            catch (AuthenticationException)
            {
                await webSocket.CloseAsync(WebSocketCloseStatus.PolicyViolation, "Invalid roomId", CancellationToken.None);
            }
        }

        private void OnDataChanged(int roomId, int personCount)
        {
            HashSet<WebSocket> sockets;

            lock (_roomWebsockets)
            {
                sockets = _roomWebsockets.GetValueOrDefault(roomId);
            }
            
            if (sockets != null)
            {
                foreach (var socket in sockets)
                {
                    SendPersonCount(socket, roomId, personCount);
                }
            }
        }
        
        private async void SendPersonCount(WebSocket webSocket, int roomId, int personCount)
        {
            var message = JsonConvert.SerializeObject(new { roomId, personCount });
            
            await WebsocketHelper.WriteString(webSocket, message);
        }
        
    }
    
}