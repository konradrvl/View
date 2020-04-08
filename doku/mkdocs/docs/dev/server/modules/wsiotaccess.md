# Websocket IoT Access

Dieses Modul stellt den **IoT-Devices** eine Websocket API bereit.

<img src="/img/server/Dependencies Graph IoTAccess.png">

**WsIoTAccess.cs**

```C#
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
```

**WsIoTAccess.cs**

```C#
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
```