using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using View.Server.Shared.Data.UserManagement;
using View.Server.WebAPI.Models;

namespace View.Server.WebAPI.Controllers
{
    [Route("api/user")]
    public class UserController : Controller
    {

        private readonly UserManager<User> _userManager;
        private readonly SignInManager<User> _signInManager;

        public UserController(UserManager<User> userManager, SignInManager<User> signInManager)
        {
            _userManager = userManager;
            _signInManager = signInManager;
        }
        
        [HttpPost]
        public async Task<IActionResult> Login([FromBody] UserLogin userLogin)
        {
            if (userLogin.Username == null || userLogin.Password == null)
            {
                return BadRequest();
            }
            
            var erg = await _signInManager.PasswordSignInAsync(userLogin.Username, userLogin.Password, userLogin.KeepLoggedIn, false);
            
            if (!erg.Succeeded)
            {
                return BadRequest();
            }
            
            return Ok();
        }
        
        [HttpPost("register")]
        public async Task<IActionResult> Register([FromBody] UserLogin userLogin)
        {
            var user = new User(userLogin.Username);

            var erg = await _userManager.CreateAsync(user, userLogin.Password);

            if (!erg.Succeeded)
            {

                return BadRequest(erg.Errors.First().Description);
            }

            await _signInManager.SignInAsync(user, isPersistent: false);
            return Ok();

        }
        
        [Authorize]
        [HttpGet("check")]
        public IActionResult Check()
        {
            return Ok();
        }

    }
}    