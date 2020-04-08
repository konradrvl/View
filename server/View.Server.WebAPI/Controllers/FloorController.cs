using System.Security.Authentication;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.Services;

namespace View.Server.WebAPI.Controllers
{
    [Authorize]
    [Route("api/floors")]
    public class FloorController : Controller
    {
        private readonly UserManager<User> _userManager;

        private readonly IFloorService _service;

        public FloorController(UserManager<User> userManager, IFloorService service)
        {
            _userManager = userManager;
            _service = service;
        }

        
        
        [HttpGet("{id}")]
        public async Task<IActionResult> Get(int id)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var floors = await _service.GetFloor(user, id);

                return Ok(floors);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
        
        [HttpGet]
        public async Task<IActionResult> GetByBuildingId(int buildingId)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var floors = await _service.GetFloorsByBuildingId(user, buildingId);

                return Ok(floors);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [HttpPost]
        public async Task<IActionResult> Create([FromBody] Floor floor)
        {
            try
            {
                await _service.AddFloor(floor);

                return Ok(floor);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Edit(int id, [FromBody] Floor floor)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                await _service.ModifyFloor(user, id, floor);

                return Ok(floor);
            }
            catch (AuthenticationException e)
            {
                
                return BadRequest(e.Message);
            }
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                await _service.DeleteFloor(user, id);

                return Ok();
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
    }
}