# Service

<img src="/img/server/Dependencies Graph Services.png">

## Services

Die Services bilden eine Zwischenschicht und verwalten die Kommunikation zwischen der WebAPI und dem DbAccess. Dazu werden die jeweiligen Data Access Klassen in die zugehörigen Services Injected.

**BuildingService.cs**

```C#
public BuildingService(IBuildingDataAccess dataAccess, IUserValidationService userValidationService)
    {
        _dataAccess = dataAccess;
        _userValidationService = userValidationService;
    }
```

In den Services werden außerdem komplexere Funktionalitäten realisiert, indem DbAccess Methoden in Kombination verwendet.

**IoTDeviceService.cs**

```C#
public async Task ModifyIoTDevice(string id, IoTDevice ioTDevice)
    {
        if (await _dataAccess.IoTDeviceIsUsed(id))
        {
            throw new DataException();
        }
        await _dataAccess.ModifyIoTDevice(id, ioTDevice);
    }
```

### User Validation Service

Der User Validation Service überprüft, ob die angeforderte Ressource zu dem entsprechenden Benutzer gehört oder nicht.
Mit diesem Service stellen die anderen Services sicher, dass die Zugriffe valide sind.

**UserValidationService.cs**

```C#
public async Task ValidateUserByBuildingId(User user, int buildingId)
    {
        var currentBuilding = await _buildingDataAccess.GetBuilding(buildingId);

        if (currentBuilding == null || currentBuilding.UserId != user.Id)
        {
            throw new AuthenticationException($"Building Id {buildingId} is invalid");
        }
    }
```

**BuildingService.cs**

```C#
public async Task<Building> GetBuilding(User user, int id)
    {
        await _userValidationService.ValidateUserByBuildingId(user, id);

        return await _dataAccess.GetBuilding(id);
    }
```

## Stores

### Occupation Service Store

Der Occupation Store verwaltet die Livedaten. Er hat die Möglichkeit Daten auf Anfrage weiter zu geben und von den Verbundenen **IoT-Devices** abzufragen. Die empfangenen Livedaten werden außerdem hier mit Zeitstempel und Raumzuordnung an den DbAccess übergeben. Hier findet auch eine Authentifizierung des **Iot-Devices** statt.

**OccupationServiceStore.cs**

```C#
public int GetCurrentPersonCount(int roomId)
    {
        lock (_liveData)
        {
            return _liveData.GetValueOrDefault(roomId, -1);
        }
    }
```

**OccupationServiceStore.cs**

```C#
private async void AddOccupation(int roomId, int personCount, DateTime time)
    {
        int? currentValue = null;

        lock (_liveData)
        {
            if (_liveData.ContainsKey(roomId))
            {
                currentValue = _liveData[roomId];
            }

            _liveData[roomId] = personCount;
        }

        if (currentValue == null || currentValue != personCount)
        {
            var task = _occupationDataAccess.AddOccupation(roomId, personCount, time);
            PersonCountChanged?.Invoke(roomId, personCount);
            await task;
        }
    }
```

**OccupationServiceStore.cs**

```C#
private async void ValidateIoTDevice(string iotDeviceId)
    {
        if (await _ioTDeviceDataAccess.IoTDeviceExists(iotDeviceId))
        {
            _ioTAccess.SetValid(iotDeviceId);

            var room = await _roomDataAccess.GetRoomByIoTDeviceId(iotDeviceId);

            if (room != null)
            {
                _ioTAccess.SetRoom(iotDeviceId, room.Id);
            }
        }
        else
        {
            _ioTAccess.SetInvalid(iotDeviceId);
        }
    }
```