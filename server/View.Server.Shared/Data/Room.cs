using System.Collections.Generic;
using Newtonsoft.Json;

namespace View.Server.Shared.Data
{
    public class Room
    {
        public int Id { get; set; }
        
        public string Name { get; set; }
        
        public int MaxPersonCount { get; set; }
        
        public int PosX { get; set; }
        public int PosY { get; set; }
        
        public int Width { get; set; }
        public int Height { get; set; }
        
        public string IoTDeviceId { get; set; }
        
        [JsonIgnore]
        public IoTDevice IoTDevice { get; set; }
        
        public int FloorId { get; set; }
        
        [JsonIgnore]
        public Floor Floor { get; set; }

        [JsonIgnore]
        public List<Occupation> Occupations { get; set; }
        
    }
}