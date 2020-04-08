using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.DbAccess
{
    public class OccupationDataAccess : IOccupationDataAccess, IDisposable
    {
        private readonly ViewDataContext _context;

        public OccupationDataAccess(ViewDataContext context)
        {
            _context = context;
        }

        public async Task AddOccupation(int roomId, int personCount, DateTime time)
        {
            var occupation = new Occupation
            {
                RoomId = roomId,
                PersonCount = personCount,
                Time = time
            };

            await _context.AddAsync(occupation);


            await _context.SaveChangesAsync();
        }

        public Task<List<Occupation>> GetOccupations(int roomId, DateTime from, DateTime to)
        {
            return _context.Occupations.Where(x => x.RoomId == roomId && from <= x.Time && x.Time <= to).ToListAsync();
        }

        public void Dispose()
        {
            _context?.Dispose();
        }
    }
}