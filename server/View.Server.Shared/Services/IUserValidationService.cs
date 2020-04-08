using System.Threading.Tasks;
using View.Server.Shared.Data.UserManagement;

namespace View.Server.Shared.Services
{
    public interface IUserValidationService
    {
        Task ValidateUserByBuildingId(User user, int buildingId);
        Task ValidateUserByFloorId(User user, int floorId);
        Task ValidateUserByRoomId(User user, int roomId);
    }
}