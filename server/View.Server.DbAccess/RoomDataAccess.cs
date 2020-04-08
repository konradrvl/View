using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.DbAccess
{
    public class RoomDataAccess : IRoomDataAccess, IDisposable
    {
      
        private readonly ViewDataContext _context;

        public RoomDataAccess(ViewDataContext context)
        {
            _context = context;
        }

        public Task<List<Room>> GetRoomsByFloorId(int floorId)
        {
            return _context.Rooms.Where(x => x.FloorId == floorId).ToListAsync();
        }

        public Task<Room> GetRoom(int id)
        {
            return _context.Rooms.Include(x => x.Floor).ThenInclude(x => x.Building).SingleOrDefaultAsync(x => x.Id == id);
        }

        public async Task AddRoom(Room room)
        {
            await _context.Rooms.AddAsync(room);

            await _context.SaveChangesAsync();
        }

        public async Task ModifyRoom(int id, Room room)
        {
            var currentRoom = await _context.Rooms.FindAsync(id);
            
            _context.Entry(currentRoom).CurrentValues.SetValues(room);
            
            await _context.SaveChangesAsync();
        }

        public async Task DeleteRoom(int id)
        {
            var room = await _context.Rooms.FindAsync(id);

            _context.Rooms.Attach(room);
            _context.Rooms.Remove(room);

            await _context.SaveChangesAsync();
        }

        public Task<Room> GetRoomByIoTDeviceId(string iotDeviceId)
        {
            return _context.Rooms.SingleOrDefaultAsync(x => x.IoTDeviceId == iotDeviceId);
        }

        public void Dispose()
        {
            _context?.Dispose();
        }
    }
}