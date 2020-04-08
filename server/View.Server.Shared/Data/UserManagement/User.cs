using System.Collections.Generic;
using Microsoft.AspNetCore.Identity;
using Newtonsoft.Json;

namespace View.Server.Shared.Data.UserManagement
{
    public class User : IdentityUser<int>
    {
        private string _userName;

        public User(string userName)
        {
            _userName = userName;
        }
        
        public override int Id { get; set; }

        public override string UserName
        {
            get => _userName;
            set => _userName = value;
        }

        public override string PasswordHash { get; set; }
        
        [JsonIgnore]
        public List<IoTDevice> IoTDevices { get; set; }
        
        [JsonIgnore]
        public List<Building> Buildings { get; set; }
    }
}