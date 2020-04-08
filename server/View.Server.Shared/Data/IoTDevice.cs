using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Data
{
    public class IoTDevice
    {
        
        public string Id { get; set; }
        
        public Room Room { get; set; }
        
        public int? UserId { get; set; }
        
        public User User { get; set; }
        
    }
}