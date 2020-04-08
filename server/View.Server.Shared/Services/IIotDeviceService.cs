using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Services
{
    public interface IIotDeviceService
    {
        Task<List<IoTDevice>> GetIoTDevices(User user);
        Task ModifyIoTDevice(string id, IoTDevice ioTDevice);
        Task<List<IoTDevice>> GetUnusedIoTDevices(User user);
    }
}