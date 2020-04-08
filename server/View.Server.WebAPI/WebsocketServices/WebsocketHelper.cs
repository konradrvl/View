using System;
using System.IO;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace View.Server.WebAPI.WebsocketServices
{
    public static class WebsocketHelper
    {
        
        public static async Task<WebsocketReadResult> ReadString(WebSocket webSocket)
        {
            var buffer = new ArraySegment<byte>(new byte[8192]);

            using (var ms = new MemoryStream())
            {
                WebSocketReceiveResult result;
                do
                {
                    result = await webSocket.ReceiveAsync(buffer, CancellationToken.None);

                    if (result.CloseStatus != null)
                    {
                        return new WebsocketReadResult
                        {
                            WebSocketCloseStatus = result.CloseStatus
                        };
                    }
                    
                    ms.Write(buffer.Array, buffer.Offset, result.Count);
                }
                while (!result.EndOfMessage);

                ms.Seek(0, SeekOrigin.Begin);

                using (var reader = new StreamReader(ms, Encoding.UTF8))
                {
                    return new WebsocketReadResult
                    {
                        Text = reader.ReadToEnd()
                    };
                }
            }
        }

        public static async Task WriteString(WebSocket webSocket, string text)
        {
            var encoded = Encoding.UTF8.GetBytes(text);
            var buffer = new ArraySegment<byte>(encoded, 0, encoded.Length);
            await webSocket.SendAsync(buffer, WebSocketMessageType.Text, true, CancellationToken.None);
        }
        
    }
    
    public class WebsocketReadResult
    {
        public string Text { get; set; }
        public WebSocketCloseStatus? WebSocketCloseStatus { get; set; }
    }
    
}