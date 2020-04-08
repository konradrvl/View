using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.Services;

namespace View.Server.Service.Services
{
    public class BuildingService : IBuildingService
    {

        private readonly IUserValidationService _userValidationService;
        
        private readonly IBuildingDataAccess _dataAccess;

        public BuildingService(IBuildingDataAccess dataAccess, IUserValidationService userValidationService)
        {
            _dataAccess = dataAccess;
            _userValidationService = userValidationService;
        }


        public async Task<Building> GetBuilding(User user, int id)
        {
            await _userValidationService.ValidateUserByBuildingId(user, id);

            return await _dataAccess.GetBuilding(id);
        }
        
        public Task<List<Building>> GetAllBuildings(User user)
        {
            return _dataAccess.GetAllBuildings(user);
        }

        public Task AddBuilding(Building building)
        {
            return _dataAccess.AddBuilding(building);
        }

        public async Task ModfiyBuilding(User user, int id, Building building)
        {
            await _userValidationService.ValidateUserByBuildingId(user, id);
            
            await _dataAccess.ModfiyBuilding(id, building);
        }

        public async Task DeleteBuilding(User user, int id)
        {
            await _userValidationService.ValidateUserByBuildingId(user, id);
            
            await _dataAccess.DeleteBuilding(id);
        }
        
    }
}