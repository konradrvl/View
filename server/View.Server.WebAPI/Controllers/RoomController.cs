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
    [Route("api/rooms")]
    public class RoomController : Controller
    {
        private readonly UserManager<User> _userManager;

        private readonly IRoomService _roomService;

        public RoomController(UserManager<User> userManager, IRoomService roomService, IOccupationService occupationService)
        {
            _userManager = userManager;
            _roomService = roomService;
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> Get(int id)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var room = await _roomService.GetRoom(user, id);

                return Ok(room);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
        
        [HttpGet]
        public async Task<IActionResult> GetRoomsByFloor(int floorId)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var rooms = await _roomService.GetRoomsByFloorId(user, floorId);

                return Ok(rooms);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [HttpPost]
        public async Task<IActionResult> Create([FromBody] Room room)
        {
            await _roomService.AddRoom(room);

            return Ok(room);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Edit(int id, [FromBody] Room room)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                await _roomService.ModifyRoom(user, id, room);

                return Ok(room);
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
                await _roomService.DeleteRoom(user, id);

                return Ok();
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
    }
}