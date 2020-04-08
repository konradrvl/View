using System.Collections.Generic;
using Newtonsoft.Json;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Data
{
    public class Building
    {
        public int Id { get; set; }
        
        public string Name { get; set; }
        
        [JsonIgnore]
        public List<Floor> Floors { get; set; }

        [JsonIgnore]
        public int UserId { get; set; }
        
        [JsonIgnore]
        public User User { get; set; }

    }
}