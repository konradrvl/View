using System.Security.Authentication;
using System.Threading.Tasks;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.Services;

namespace View.Server.Service.Services
{

    public class UserValidationService : IUserValidationService
    {
        private readonly IRoomDataAccess _roomDataAccess;
        private readonly IFloorDataAccess _floorDataAccess;
        private readonly IBuildingDataAccess _buildingDataAccess;

        public UserValidationService(IRoomDataAccess roomDataAccess, IFloorDataAccess floorDataAccess, IBuildingDataAccess buildingDataAccess)
        {
            _roomDataAccess = roomDataAccess;
            _floorDataAccess = floorDataAccess;
            _buildingDataAccess = buildingDataAccess;
        }


        public async Task ValidateUserByBuildingId(User user, int buildingId)
        {
            var currentBuilding = await _buildingDataAccess.GetBuilding(buildingId);
            
            if (currentBuilding == null || currentBuilding.UserId != user.Id)
            {
                throw new AuthenticationException($"Building Id {buildingId} is invalid");
            }
        }

        public async Task ValidateUserByFloorId(User user, int floorId)
        {
            var currentFloor = await _floorDataAccess.GetFloor(floorId);

            if (currentFloor == null ||currentFloor.Building.UserId != user.Id)
            {
                throw new AuthenticationException($"Floor Id {floorId} is invalid");
            }
        }
        
        public async Task ValidateUserByRoomId(User user, int roomId)
        {
            var currentRoom = await _roomDataAccess.GetRoom(roomId);

            if (currentRoom == null || currentRoom.Floor.Building.UserId != user.Id)
            {
                throw new AuthenticationException($"Room Id {roomId} is invalid");
            }
        }
        
    }
}