using System;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using View.Server.DbAccess;
using View.Server.Service.Services;
using View.Server.Service.Stores;
using View.Server.Shared.Data.UserManagement;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.IoTAccess;
using View.Server.Shared.Services;
using View.Server.WebAPI.Proxies.DataAccesses;
using View.Server.WebAPI.Proxies.Services;
using View.Server.WebAPI.WebsocketServices;
// ReSharper disable MemberCanBeMadeStatic.Local

// ReSharper disable UnusedMember.Global

namespace View.Server.WebAPI
{
    public class Startup
    {
        private IConfiguration Configuration { get; set; }
        
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }
        
        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddScoped<IOccupationService, OccupationService>();
            services.AddScoped<IBuildingService, BuildingService>();
            services.AddScoped<IFloorService, FloorService>();
            services.AddScoped<IRoomService, RoomService>();
            services.AddScoped<IUserValidationService, UserValidationService>();
            services.AddScoped<IIotDeviceService, IoTDeviceService>();

            services.AddScoped<IOccupationDataAccess, OccupationDataAccess>();
            services.AddScoped<IBuildingDataAccess, BuildingDataAccess>();
            services.AddScoped<IFloorDataAccess, FloorDataAccess>();
            services.AddScoped<IRoomDataAccess, RoomDataAccess>();
            services.AddScoped<IIoTDeviceDataAccess, IoTDeviceDataAccess>();

            ConfigureOcupationServiceStore(services);

            ConfigureFrontendWebsocketService(services);
            
            services.AddSingleton<IIoTAccess, WsIoTAccess.WsIoTAccess>();

            services.AddDbContext<ViewDataContext>(options => options.UseMySql(Configuration.GetSection("database").Value));

            ConfigureIdentification(services);
            
            services.AddMvc();
        }

        private static void ConfigureOcupationServiceStore(IServiceCollection services)
        {
            services.AddSingleton(x =>
            {
                var wsIoTAccess = x.GetRequiredService<IIoTAccess>();
                var iotDataAccess = new IoTDeviceDataAccessScopedProxy(services);
                var roomDataAccess = new RoomDataAccessScopedProxy(services);
                var occupationDataAccess = new OccupationDataAccessScopedProxy(services);
                
                return new OcupationServiceStore(wsIoTAccess, occupationDataAccess, roomDataAccess, iotDataAccess);
            });
        }

        private static void ConfigureFrontendWebsocketService(IServiceCollection services)
        {
            services.AddSingleton(x =>
            {
                var ocupationServiceStore = x.GetRequiredService<OcupationServiceStore>();
                var userValidationService = new UserValidationServiceScopedProxy(services);
                
                return new FrontendWebsocketService(ocupationServiceStore, userValidationService);
            });
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env, IApplicationLifetime lifetime)
        {
            app.MapWhen(context => !context.Request.Path.Value.StartsWith("/api"), ConfigureStaticFiles);
            
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseCookiePolicy();

            app.UseAuthentication();

            app.UseWebSockets();
           
            app.UseMvc();
            
            // Instantiate Occupation Store so new person counts will be noticed and added to the database
            app.ApplicationServices.GetService<OcupationServiceStore>();
            
            // Start Websocket for IoTDeviceConnection
            var ws = app.ApplicationServices.GetService<IIoTAccess>();
            ws.Start();

            // Stop Websocket on Application exit to free port
            AppDomain.CurrentDomain.ProcessExit += (e, o) => ws.Stop();
            lifetime.ApplicationStopped.Register(ws.Stop);
        }

        private void ConfigureStaticFiles(IApplicationBuilder app)
        {
            app.Use((context, next) =>
            {
                if(!context.Request.Path.Value.Contains("."))
                {
                    context.Request.Path = "/index.html";
                }
                    
                return next();
            });
                
            app.UseStaticFiles();
        }
        
        private void ConfigureIdentification(IServiceCollection services)
        {
            services.AddIdentity<User, IdentityRole<int>>()
                .AddEntityFrameworkStores<ViewDataContext>()
                .AddDefaultTokenProviders();

            services.AddAuthentication(options =>
            {
                options.DefaultScheme = IdentityConstants.ApplicationScheme;
                options.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
            }).AddJwtBearer();
            
            services.Configure<IdentityOptions>(options =>
            {
                options.SignIn.RequireConfirmedEmail = false;
                options.SignIn.RequireConfirmedPhoneNumber = false;
                
                options.Password.RequireDigit = false;
                options.Password.RequiredLength = 0;
                options.Password.RequiredUniqueChars = 0;
                options.Password.RequireLowercase = false;
                options.Password.RequireNonAlphanumeric = false;
                options.Password.RequireUppercase = false;
                
            });

            services.ConfigureApplicationCookie(options =>
            {
                // Cookie settings
                options.Cookie.Name = "Authentication";
                options.Cookie.HttpOnly = true;
                options.ExpireTimeSpan = TimeSpan.FromMinutes(30);
                // If the LoginPath isn't set, ASP.NET Core defaults 
                // the path to /Account/Login.
                options.LoginPath = "/api/user";
                // If the AccessDeniedPath isn't set, ASP.NET Core defaults 
                // the path to /Account/AccessDenied.
                //options.AccessDeniedPath = "/Account/AccessDenied";
                options.SlidingExpiration = true;
            });
        }
        
    }
}