using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.WebAPI.Proxies.DataAccesses
{
    public class RoomDataAccessScopedProxy : IRoomDataAccess
    {
        
        private readonly IServiceCollection _services;

        public RoomDataAccessScopedProxy(IServiceCollection services)
        {
            _services = services;
        }

        public async Task<List<Room>> GetRoomsByFloorId(int floorId)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IRoomDataAccess>();
                return await obj.GetRoomsByFloorId(floorId);
            }
        }

        public async Task<Room> GetRoom(int id)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IRoomDataAccess>();
                return await obj.GetRoom(id);
            }
        }

        public Task AddRoom(Room room)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IRoomDataAccess>();
                return obj.AddRoom(room);
            }
        }

        public async Task ModifyRoom(int id, Room room)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IRoomDataAccess>();
                await obj.ModifyRoom(id, room);
            }
        }

        public async Task DeleteRoom(int id)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IRoomDataAccess>();
                await obj.DeleteRoom(id);
            }
        }

        public async Task<Room> GetRoomByIoTDeviceId(string iotDeviceId)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IRoomDataAccess>();
                return await obj.GetRoomByIoTDeviceId(iotDeviceId);
            }
        }
    }
}