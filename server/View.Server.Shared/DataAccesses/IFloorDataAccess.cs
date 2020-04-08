using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;

namespace View.Server.Shared.DataAccesses
{
    public interface IFloorDataAccess
    {
        Task<List<Floor>> GetFloorsByBuildingId(int buildingId);
        Task<Floor> GetFloor(int id);
        Task AddFloor(Floor floor);
        Task ModifyFloor(int id, Floor floor);
        Task DeleteFloor(int id);
    }
}