using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using View.Server.Shared.Data;

namespace View.Server.Shared.DataAccesses
{
    public interface IOccupationDataAccess
    {
        Task AddOccupation(int roomId, int personCount, DateTime time);
        
        Task<List<Occupation>> GetOccupations(int roomId, DateTime from, DateTime to);
        
    }
}