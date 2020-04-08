using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.Services;

namespace View.Server.Service.Services
{
    public class FloorService : IFloorService
    {
        
        private readonly IUserValidationService _userValidationService;
        
        private readonly IFloorDataAccess _dataAccess;

        public FloorService(IFloorDataAccess dataAccess, IUserValidationService userValidationService)
        {
            _dataAccess = dataAccess;
            _userValidationService = userValidationService;
        }

        public async Task<Floor> GetFloor(User user, int id)
        {
            await _userValidationService.ValidateUserByFloorId(user, id);
            
            return await _dataAccess.GetFloor(id);
        }
        
        public async Task<List<Floor>> GetFloorsByBuildingId(User user, int buildingId)
        {
            await _userValidationService.ValidateUserByBuildingId(user, buildingId);
            
            return await _dataAccess.GetFloorsByBuildingId(buildingId);
        }

        public Task AddFloor(Floor floor)
        {
            return _dataAccess.AddFloor(floor);
        }

        public async Task ModifyFloor(User user, int id, Floor floor)
        {
            await _userValidationService.ValidateUserByFloorId(user, id);

            await _dataAccess.ModifyFloor(id, floor);
        }

        public async Task DeleteFloor(User user, int id)
        {
            await _userValidationService.ValidateUserByFloorId(user, id);

            await _dataAccess.DeleteFloor(id);
        }
        
    }
}