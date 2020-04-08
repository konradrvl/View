# WebAPI

<img src="/img/server/Dependencies Graph WebAPI.png">

Die WebAPI ist das Startprojekt des Servers. Von hier aus wird die **Webapplikation** ausgeliefert, außerdem
wird hier die HTTP API und die Websocket API für die **Webapplikation** zur Verfügung gestellt. Hier werden auch die Injectable Objekte
für das ASP.Net Framework definiert.

**Startup.cs**

```C#
public void ConfigureServices(IServiceCollection services)
        {
            services.AddScoped<IOccupationService, OccupationService>();
            services.AddScoped<IBuildingService, BuildingService>();
            services.AddScoped<IFloorService, FloorService>();
            services.AddScoped<IRoomService, RoomService>();
            services.AddScoped<IUserValidationService, UserValidationService>();
            services.AddScoped<IIotDeviceService, IoTDeviceService>();

            ...

        }
```

**Startup.cs**

```C#
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
            
            ...

        }
```

**Program.cs**


```C#
 public class Program
    {
        public static void Main(string[] args)
        {
            var config = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json")
                .Build();

            WebHost.CreateDefaultBuilder(args)
                .UseStartup<Startup>()
                ...
        }
    }
```

## Controllers

Die Controller sind ein Baustein des ASP.NET Frameworks und bilden die HTTP API des Servers.
Hier werden über HTTP Verben Funktionen angeboten. Die Authentifikation wird durch die `[Authorize]`
Annotation vom Framework übernommen. In einem Fehlerfall wird ein HTTP Error zurückgegeben.

**BuildingController.cs**

```C#
[Authorize]
[Route("api/buildings")]
public class BuildingController : Controller
{
    private readonly UserManager<User> _userManager;

    private readonly IBuildingService _service;

    ...

```

**FloorController.cs**

```C#
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
```

## Proxies

Die Proxies dienen dazu, der Websocket API und dem WsIoTAccess transaktionsbasierten Zugriff auf die Datenbank zu ermöglichen. Bei Controllern ist das nicht nötig, da diese standardmäßig transaktionsbasiert arbeiten. Ein Websocket bleibt dagegen dauerhaft geöffnet. Das führt dazu, dass beim öffnen eines Websockets ein Scope erstellt und bis zum schließen beibehalten wird. Durch die Proxys wird für jeden Methodenaufruf ein neues Scope angefordert und die Websocket API wird somit auch transaktionsbasiert.

Auch im Occupation Store werden Proxies verwendet, da dieser Singelton ist und einmal bei Programmstart initialisiert wird.

**IoTDeviceDataAccessScopedProxy.cs**

```C#
public async Task<List<IoTDevice>> GetIoTDevices(int userId)
{
    using (var scope = _services.BuildServiceProvider().CreateScope())
    {
        var obj = scope.ServiceProvider.GetRequiredService<IIoTDeviceDataAccess>();
        return await obj.GetIoTDevices(userId);
    }
}
```

## Websocket Services

Hier wird die Websocket API zur Verfügung gestellt. Die **Webapplikation** muss sich mit einer roomID ein Abonnement anfordern und bekommt dann die aktuellen Belegungsdaten live gesendet. Die Websocket-Schnittstelle benutzt hierfür die Authentifizierung die auch bei den Controllern eingesetzt wird.

**FrontendWebsocketService.cs**

```C#
private async void HandleNewRoomRegistration(WebSocket webSocket, IEnumerable<int> roomIds, User user)
{
    try
    {
        foreach (var roomId in roomIds)
        {
            await _userValidationService.ValidateUserByRoomId(user, roomId);

            lock (_roomWebsockets)
            {
                if (!_roomWebsockets.ContainsKey(roomId))
                {
                    _roomWebsockets[roomId] = new HashSet<WebSocket>();
                }

                _roomWebsockets[roomId].Add(webSocket);

                var currentPersonCount = _ocupationServiceStore.GetCurrentPersonCount(roomId);
                SendPersonCount(webSocket, roomId, currentPersonCount);
            }
        }
    }
    catch (AuthenticationException)
    {
        await webSocket.CloseAsync(WebSocketCloseStatus.PolicyViolation, "Invalid roomId", CancellationToken.None);
    }
}
```

**FrontendWebsocketService.cs**

```C#
private async void OnMessage(WebSocket webSocket, string message, User user)
{
    try
    {
        var roomIds = JsonConvert.DeserializeObject<int[]>(message);
        HandleNewRoomRegistration(webSocket, roomIds, user);
    }
    catch (JsonReaderException)
    {
        await webSocket.CloseAsync(WebSocketCloseStatus.PolicyViolation, "Got illegal message. Expected roomIds", CancellationToken.None);
    }
}
```
