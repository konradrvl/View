using System.Collections.Generic;
using Newtonsoft.Json;

namespace View.Server.Shared.Data
{
    public class Floor
    {
        public int Id { get; set; }
        
        public string Name { get; set; }
        
        public int BuildingId { get; set; }
        
        [JsonIgnore]
        public Building Building { get; set; }
        
        [JsonIgnore]
        public List<Room> Rooms { get; set; }
    }
}