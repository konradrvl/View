using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;

namespace View.Server.Shared.DataAccesses
{
    public interface IRoomDataAccess
    {
        Task<List<Room>> GetRoomsByFloorId(int floorId);
        Task<Room> GetRoom(int id);
        Task AddRoom(Room room);
        Task ModifyRoom(int id, Room room);
        Task DeleteRoom(int id);
        
        Task<Room> GetRoomByIoTDeviceId(string iotDeviceId);
    }
}