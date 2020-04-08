using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.DataAccesses
{
    public interface IIoTDeviceDataAccess
    {
        Task<List<IoTDevice>> GetIoTDevices(int userId);
        Task<bool> IoTDeviceExists(string id);
        Task<bool> IoTDeviceIsUsed(string id);
        Task ModifyIoTDevice(string id, IoTDevice ioTDevice);
        Task<List<IoTDevice>> GetUnusedIoTDevices(int userId);
    }
}