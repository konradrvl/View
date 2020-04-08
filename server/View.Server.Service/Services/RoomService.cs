using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.IoTAccess;
using View.Server.Shared.Services;

namespace View.Server.Service.Services
{
    public class RoomService : IRoomService
    {
        
        private readonly IUserValidationService _userValidationService;
        
        private readonly IRoomDataAccess _dataAccess;

        private readonly IIoTAccess _iioTAccess;
        
        public RoomService(IRoomDataAccess dataAccess, IIoTAccess iioTAccess, IUserValidationService userValidationService)
        {
            _dataAccess = dataAccess;
            _iioTAccess = iioTAccess;
            _userValidationService = userValidationService;
        }

        public async Task<Room> GetRoom(User user, int roomId)
        {
            await _userValidationService.ValidateUserByRoomId(user, roomId);
            
            return await _dataAccess.GetRoom(roomId);
        }
        
        public async Task<List<Room>> GetRoomsByFloorId(User user, int floorId)
        {
            await _userValidationService.ValidateUserByFloorId(user, floorId);
            
            return await _dataAccess.GetRoomsByFloorId(floorId);
        }

        public async Task AddRoom(Room room)
        {
            await _dataAccess.AddRoom(room);
            
            UpdateRoomId(room);
        }

        public async Task ModifyRoom(User user, int id, Room room)
        {
            await _userValidationService.ValidateUserByRoomId(user, id);
            
            await _dataAccess.ModifyRoom(id, room);

            UpdateRoomId(room);
        }

        public async Task DeleteRoom(User user, int id)
        {
            await _userValidationService.ValidateUserByRoomId(user, id);

            await _dataAccess.DeleteRoom(id);
            
            _iioTAccess.DeleteRoom(id);
        }

        public Task<Room> GetRoomByIoTDeviceId(string iotDeviceKey)
        {
            return _dataAccess.GetRoomByIoTDeviceId(iotDeviceKey);
        }
        
        private void UpdateRoomId(Room room)
        {
            if (room.IoTDeviceId != null)
            {
                _iioTAccess.SetRoom(room.IoTDeviceId, room.Id);
            }
            else
            {
                _iioTAccess.DeleteRoom(room.Id);
            }
        }
    }
}