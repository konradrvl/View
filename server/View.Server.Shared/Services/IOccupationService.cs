using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Services
{
    public interface IOccupationService
    {
        Task<int> GetCurrentPersonCount(User user, int roomId);
        Task<List<Occupation>> GetOccupations(User user, int roomId, DateTime from, DateTime to);
    }
}