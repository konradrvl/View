using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.WebAPI.Proxies.DataAccesses
{
    public class IoTDeviceDataAccessScopedProxy : IIoTDeviceDataAccess
    {
        private readonly IServiceCollection _services;

        public IoTDeviceDataAccessScopedProxy(IServiceCollection services)
        {
            _services = services;
        }

        public async Task<List<IoTDevice>> GetIoTDevices(int userId)
        {
            using (var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IIoTDeviceDataAccess>();
                return await obj.GetIoTDevices(userId);
            }
        }

        public async Task<bool> IoTDeviceExists(string id)
        {
            using (var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IIoTDeviceDataAccess>();
                return await obj.IoTDeviceExists(id);
            }
        }

        public async Task<bool> IoTDeviceIsUsed(string id)
        {
            using (var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IIoTDeviceDataAccess>();
                return await obj.IoTDeviceIsUsed(id);
            }
        }

        public async Task ModifyIoTDevice(string id, IoTDevice ioTDevice)
        {
            using (var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IIoTDeviceDataAccess>();
                await obj.ModifyIoTDevice(id, ioTDevice);
            }
        }

        public async Task<List<IoTDevice>> GetUnusedIoTDevices(int userId)
        {
            using (var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IIoTDeviceDataAccess>();
                return await obj.GetUnusedIoTDevices(userId);
            }
        }
    }
}