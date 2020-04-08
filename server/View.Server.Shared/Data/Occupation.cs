using System;
using Newtonsoft.Json;

namespace View.Server.Shared.Data
{
    public class Occupation
    {
        
        public int Id { get; set; }
        
        public int RoomId { get; set; }
        
        [JsonIgnore]
        public Room Room { get; set; }
     
        public DateTime Time { get; set; }
        
        public int PersonCount { get; set; }
        
    }
}