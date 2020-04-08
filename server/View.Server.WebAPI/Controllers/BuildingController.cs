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
    [Route("api/buildings")]
    public class BuildingController : Controller
    {
        private readonly UserManager<User> _userManager;

        private readonly IBuildingService _service;
        
        /// <summary>
        /// This is a constructor
        /// </summary>
        /// <param name="userManager"></param>
        /// <param name="service"></param>
        public BuildingController(UserManager<User> userManager, IBuildingService service)
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
                var buildings = await _service.GetBuilding(user, id);

                return Ok(buildings);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [HttpGet]
        public async Task<IActionResult> Get()
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var buildings = await _service.GetAllBuildings(user);

                return Ok(buildings);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [HttpPost]
        public async Task<IActionResult> Create([FromBody] Building building)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);

                building.UserId = user.Id;

                await _service.AddBuilding(building);

                return Ok(building);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Edit(int id, [FromBody] Building building)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                building.UserId = user.Id;
                await _service.ModfiyBuilding(user, id, building);

                return Ok(building);
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
                await _service.DeleteBuilding(user, id);

                return Ok();
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
    }
}