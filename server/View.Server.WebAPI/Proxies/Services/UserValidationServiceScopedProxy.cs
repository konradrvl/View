using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.Services;

namespace View.Server.WebAPI.Proxies.Services
{
    public class UserValidationServiceScopedProxy : IUserValidationService
    {
        
        private readonly IServiceCollection _services;

        public UserValidationServiceScopedProxy(IServiceCollection services)
        {
            _services = services;
        }

        public async Task ValidateUserByBuildingId(User user, int buildingId)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IUserValidationService>();
                await obj.ValidateUserByBuildingId(user, buildingId);
            }
        }

        public async Task ValidateUserByFloorId(User user, int floorId)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IUserValidationService>();
                await obj.ValidateUserByFloorId(user, floorId);
            }
        }

        public async Task ValidateUserByRoomId(User user, int roomId)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IUserValidationService>();
                await obj.ValidateUserByRoomId(user, roomId);
            }
        }
    }
}