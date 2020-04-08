using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.DbAccess
{
    public class IoTDeviceDataAccess : IIoTDeviceDataAccess, IDisposable
    {
        
        private readonly ViewDataContext _context;

        public IoTDeviceDataAccess(ViewDataContext context)
        {
            _context = context;
        }
        
        public Task<List<IoTDevice>> GetIoTDevices(int userId)
        {
            return _context.IoTDevices.Where(x => x.UserId == userId).ToListAsync();
        }

        public Task<bool> IoTDeviceExists(string id)
        {
            return _context.IoTDevices.AnyAsync(x => x.Id == id);
        }
        
        public Task<bool> IoTDeviceIsUsed(string id)
        {
            return _context.IoTDevices.AnyAsync(x => x.Id == id && x.UserId != null);
        }

        public async Task ModifyIoTDevice(string id, IoTDevice ioTDevice)
        {
            var oldIoTDevice = await _context.IoTDevices.FindAsync(id);
            
            _context.Entry(oldIoTDevice).CurrentValues.SetValues(ioTDevice);
            
            await _context.SaveChangesAsync();
        }

        public Task<List<IoTDevice>> GetUnusedIoTDevices(int userId)
        {
            return _context.IoTDevices.Include(x => x.Room).Where(x => x.UserId == userId && x.Room == null).ToListAsync();
        }

        public void Dispose()
        {
            _context?.Dispose();
        }
    }
}