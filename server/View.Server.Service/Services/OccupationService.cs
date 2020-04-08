using System;
using System.Collections.Generic;
using System.Security.Authentication;
using System.Threading.Tasks;
using View.Server.Service.Stores;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.Services;

namespace View.Server.Service.Services
{
    public class OccupationService : IOccupationService
    {

        private readonly IUserValidationService _userValidationService;
        
        private readonly IOccupationDataAccess _occupationDataAccess;
        
        private readonly OcupationServiceStore _ocupationServiceStore;

        public OccupationService(IOccupationDataAccess occupationDataAccess, OcupationServiceStore ocupationServiceStore, IUserValidationService userValidationService)
        {
            _occupationDataAccess = occupationDataAccess;
            _ocupationServiceStore = ocupationServiceStore;
            _userValidationService = userValidationService;
        }

        public async Task<List<Occupation>> GetOccupations(User user, int roomId, DateTime from, DateTime to)
        {
            await _userValidationService.ValidateUserByRoomId(user, roomId);
            
            var occupations = await _occupationDataAccess.GetOccupations(roomId, from, to);

            return occupations;
        }

        public async Task<int> GetCurrentPersonCount(User user, int roomId)
        {
            await _userValidationService.ValidateUserByRoomId(user, roomId);
            
            return _ocupationServiceStore.GetCurrentPersonCount(roomId);
        }
        
    }
}
