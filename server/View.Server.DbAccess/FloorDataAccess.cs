using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using View.Server.Shared.Data;
using View.Server.Shared.DataAccesses;

namespace View.Server.DbAccess
{
    public class FloorDataAccess : IFloorDataAccess
    {
        private readonly ViewDataContext _context;

        public FloorDataAccess(ViewDataContext context)
        {
            _context = context;
        }

        public Task<List<Floor>> GetFloorsByBuildingId(int buildingId)
        {
            return _context.Floors.Where(x => x.BuildingId == buildingId).ToListAsync();
        }

        public Task<Floor> GetFloor(int id)
        {
            return _context.Floors.Include(x => x.Building).SingleOrDefaultAsync(x => x.Id == id);
        }
        
        public async Task AddFloor(Floor floor)
        {
            await _context.Floors.AddAsync(floor);

            await _context.SaveChangesAsync();
        }

        public async Task ModifyFloor(int id, Floor floor)
        {
            var currentFloor = await _context.Floors.FindAsync(id);
            
            _context.Entry(currentFloor).CurrentValues.SetValues(floor);
            
            await _context.SaveChangesAsync();
        }

        public async Task DeleteFloor(int id)
        {
            var floor = await _context.Floors.FindAsync(id);

            _context.Floors.Attach(floor);
            _context.Floors.Remove(floor);

            await _context.SaveChangesAsync();
        }
    }
}