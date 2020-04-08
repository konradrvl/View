using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.WebAPI.Proxies.DataAccesses
{
    public class OccupationDataAccessScopedProxy : IOccupationDataAccess
    {

        private readonly IServiceCollection _services;

        public OccupationDataAccessScopedProxy(IServiceCollection services)
        {
            _services = services;
        }

        public async Task AddOccupation(int roomId, int personCount, DateTime time)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IOccupationDataAccess>();
                await obj.AddOccupation(roomId, personCount, time);
            }
        }

        public async Task<List<Occupation>> GetOccupations(int roomId, DateTime from, DateTime to)
        {
            using(var scope = _services.BuildServiceProvider().CreateScope())
            {
                var obj = scope.ServiceProvider.GetRequiredService<IOccupationDataAccess>();
                return await obj.GetOccupations(roomId, from, to);
            }
        }
    }
}