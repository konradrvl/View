using System;

namespace View.Server.WsIoTAccess.Messages.Parameters
{
    public class PersonCountChangedParameters
    {
        public int PersonCount { get; set; }
        
        public DateTime TimeStamp { get; set; }
    }
}