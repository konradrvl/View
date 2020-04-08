using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Services
{
    public interface IFloorService
    {
        Task<Floor> GetFloor(User user, int id);
        Task<List<Floor>> GetFloorsByBuildingId(User user, int buildingId);
        Task AddFloor(Floor floor);
        Task ModifyFloor(User user, int id, Floor floor);
        Task DeleteFloor(User user, int id);
    }
}