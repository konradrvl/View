using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Services
{
    public interface IBuildingService
    {
        Task<Building> GetBuilding(User user, int id);
        Task<List<Building>> GetAllBuildings(User user);
        Task AddBuilding(Building building);
        Task ModfiyBuilding(User user, int id, Building building);
        Task DeleteBuilding(User user, int id);
    }
}