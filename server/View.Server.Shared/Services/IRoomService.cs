using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Services
{
    public interface IRoomService
    {
        Task<Room> GetRoom(User user, int roomId);
        Task<List<Room>> GetRoomsByFloorId(User user, int floorId);
        Task AddRoom(Room room);
        Task ModifyRoom(User user, int id, Room room);
        Task DeleteRoom(User user, int id);

        Task<Room> GetRoomByIoTDeviceId(string iotDeviceKey);
    }
}