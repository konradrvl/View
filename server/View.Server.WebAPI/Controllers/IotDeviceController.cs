using System.Linq;
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
    [Route("api/iotDevices")]
    public class IotDeviceController : Controller
    {
        private readonly UserManager<User> _userManager;

        private readonly IIotDeviceService _service;

        public IotDeviceController(UserManager<User> userManager, IIotDeviceService service)
        {
            _userManager = userManager;
            _service = service;
        }
        
        [HttpGet]
        public async Task<IActionResult> Get()
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var ioTDevices = await _service.GetIoTDevices(user);

                return Ok(ioTDevices.Select(x => x.Id));
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
        
        [HttpGet("unused")]
        public async Task<IActionResult> GetUnused()
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                var ioTDevices = await _service.GetUnusedIoTDevices(user);

                return Ok(ioTDevices.Select(x => x.Id));
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
        
        [HttpPut("{id}")]
        public async Task<IActionResult> Edit(string id)
        {
            try
            {
                var user = await _userManager.GetUserAsync(User);
                
                var device = new IoTDevice {Id = id, UserId = user.Id};
                await _service.ModifyIoTDevice(id, device);

                return Ok(device);
            }
            catch (AuthenticationException e)
            {
                return BadRequest(e.Message);
            }
        }
    }
}