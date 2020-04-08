using System;
using System.Security.Authentication;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.Services;
using View.Server.WebAPI.WebsocketServices;

namespace View.Server.WebAPI.Controllers
{
    [Route("api/occupations")]
    public class OccupationController : Controller
    {
        private readonly UserManager<User> _userManager;

        private readonly IOccupationService _occupationService;

        private readonly FrontendWebsocketService _frontendWebsocketService;

        public OccupationController(IOccupationService occupationService,
            FrontendWebsocketService frontendWebsocketService, UserManager<User> userManager)
        {
            _occupationService = occupationService;
            _frontendWebsocketService = frontendWebsocketService;
            _userManager = userManager;
        }

        [Authorize]
        [HttpGet("history")]
        public async Task<IActionResult> GetOccupations(int roomId, DateTime from, DateTime to)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var data = await _occupationService.GetOccupations(user, roomId, from, to);

                return Ok(data);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [Authorize]
        [HttpGet("current")]
        public async Task<IActionResult> GetCurrentPersonCount(int roomId)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var data = await _occupationService.GetCurrentPersonCount(user, roomId);

                return Ok(data);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }

        [Authorize]
        [Route("ws-frontend")]
        public async Task FrontendWebsocket()
        {
            if (HttpContext.WebSockets.IsWebSocketRequest)
            {
                var webSocket = await HttpContext.WebSockets.AcceptWebSocketAsync();
                var user = await _userManager.GetUserAsync(User);

                await _frontendWebsocketService.Start(webSocket, user);
            }
        }
    }
}