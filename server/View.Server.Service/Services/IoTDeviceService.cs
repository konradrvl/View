using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.Services;

namespace View.Server.Service.Services
{
    public class IoTDeviceService : IIotDeviceService
    {
        private readonly IUserValidationService _userValidationService;
        
        private readonly IIoTDeviceDataAccess _dataAccess;

        public IoTDeviceService(IIoTDeviceDataAccess dataAccess, IUserValidationService userValidationService)
        {
            _dataAccess = dataAccess;
            _userValidationService = userValidationService;
        }

        public async Task<List<IoTDevice>> GetIoTDevices(User user)
        {
            return await _dataAccess.GetIoTDevices(user.Id);
        }

        public async Task ModifyIoTDevice(string id, IoTDevice ioTDevice)
        {
            if (await _dataAccess.IoTDeviceIsUsed(id))
            {
                throw new DataException();
            }
            await _dataAccess.ModifyIoTDevice(id, ioTDevice);
        }

        public async Task<List<IoTDevice>> GetUnusedIoTDevices(User user)
        {
            return await _dataAccess.GetUnusedIoTDevices(user.Id);
        }
    }
}