namespace View.Server.WsIoTAccess.Messages
{
    public class IoTMessage<T>
    {
        
        public MessageType MessageType { get; set; }
        
        public T Parameters { get; set; }
        
    }
}