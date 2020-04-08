# DbAccess

<img src="/img/server/Dependencies Graph DataAccess.png">

## View Data Context

In dieser Klasse wird die Datenbank definiert und bei Bedarf angelegt. Die Klasse erbt von `dbContext` aus dem Entity Framework
und wird später durch ASP.NET in die Data Access Objekte Injected.

**ViewDataContext.cs**

```C#
protected override void OnModelCreating(ModelBuilder modelBuilder)
{
    modelBuilder.Entity<IdentityUserRole<int>>().HasKey(p => new { p.UserId, p.RoleId });

    modelBuilder.Entity<IoTDevice>()
        .HasOne(x => x.User)
        .WithMany(x => x.IoTDevices)
        .HasForeignKey(x => x.UserId)
        .IsRequired(false);

    modelBuilder.Entity<Room>()
        .HasOne(x => x.IoTDevice)
        .WithOne(x => x.Room)
        .HasForeignKey<Room>(x => x.IoTDeviceId)
        .IsRequired(false);
}
```

## Data Access

Die Data Access Klassen erben ihre entsprechenden Interfaces aus dem Shared Modul und verwalten den Zugriff auf die Datenbank.
Der oben definierte `_context` wird dabei in den Konstruktor Injected.

**IoTDeviceDataAccess.cs**

```C#
private readonly ViewDataContext _context;

    public IoTDeviceDataAccess(ViewDataContext context)
    {
        _context = context;
    }
```

Über den `_context` können dann mittels Fluent API Datenbankzugriffe stattfinden.

**IoTDeviceDataAccess.cs**

```C#
public Task<List<IoTDevice>> GetIoTDevices(int userId)
    {
        return _context.IoTDevices.Where(x => x.UserId == userId).ToListAsync();
    }
```

Hier werden zum Beispiel Belegungswerte anhand einer RaumId und einem Zeitintervall aus der Datenbank ausgelesen.

**OccupationDataAccess.cs**

```C#
public Task<List<Occupation>> GetOccupations(int roomId, DateTime from, DateTime to)
    {
        return _context.Occupations.Where(x => x.RoomId == roomId && from <= x.Time && x.Time <= to).ToListAsync();
    }
```