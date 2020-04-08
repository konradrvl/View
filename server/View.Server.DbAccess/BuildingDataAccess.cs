using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;

namespace View.Server.DbAccess
{
    public class BuildingDataAccess : IBuildingDataAccess
    {

        private readonly ViewDataContext _context;

        public BuildingDataAccess(ViewDataContext context)
        {
            _context = context;
        }
        
        public Task<Building> GetBuilding(int id)
        {
            return _context.Buildings.FindAsync(id);
        }

        public Task<List<Building>> GetAllBuildings(User user)
        {
            return _context.Buildings.Where(x => x.UserId == user.Id).ToListAsync();
        }

        public async Task AddBuilding(Building building)
        {
            await _context.Buildings.AddAsync(building);

            await _context.SaveChangesAsync();
        }

        public async Task ModfiyBuilding(int id, Building building)
        {
            var currentBuilding = await _context.Buildings.FindAsync(id);
            
            _context.Entry(currentBuilding).CurrentValues.SetValues(building);
            
            await _context.SaveChangesAsync();
        }

        public async Task DeleteBuilding(int id)
        {
            var building = await _context.Buildings.FindAsync(id);

            _context.Buildings.Attach(building);
            _context.Buildings.Remove(building);

            await _context.SaveChangesAsync();
        }
    }
}