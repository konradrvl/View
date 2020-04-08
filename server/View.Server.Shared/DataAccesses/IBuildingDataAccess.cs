using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.DataAccesses
{
    public interface IBuildingDataAccess
    {
        Task<Building> GetBuilding(int id);
        Task<List<Building>> GetAllBuildings(User user);
        Task AddBuilding(Building building);
        Task ModfiyBuilding(int id, Building building);
        Task DeleteBuilding(int id);
    }
}