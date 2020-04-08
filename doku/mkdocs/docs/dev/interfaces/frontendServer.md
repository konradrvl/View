# Frontend <-> Server

Die Kommunikation zwischen Frontend und Server wird über 2 Schnittstellen realisiert:

+ HTTP WebAPI
+ Websockets

## HTTP WebAPI

Folgende Aufrufe sind vom Client (Frontend) zum Server möglich:

### Benutzer

| URL                | HTTP Verb | Parameters | Authorized | Bedeutung            |
| ------------------ | --------- | ---------- | ---------- | -------------------- |
| /api/user          | POST      | UserLogin  |            | Login                |
| /api/user/register | POST      | UserLogin  |            | Register             |
| /api/user/check    | GET       |            | X          | Auf Anmeldung prüfen |

Beispiel UserLogin:

```json
{
    "username": "Peter",
    "password": "GanzGeheimesPassword1",
    "keepLoggedIn": true
}
```

### Gebäude

| URL                      | HTTP Verb | Parameters | Authorized | Bedeutung                         |
| ------------------------ | --------- | ---------- | ---------- | --------------------------------- |
| /api/buildings/{id: int} | GET       |            | X          | Liefert ein Gebäude anhand der ID |
| /api/buildings           | GET       |            | X          | Liefert alle Gebäude              |
| /api/buildings/          | POST      | Building   | X          | Legt ein neues Gebäude an         |
| /api/buildings/{id: int} | PUT       | Building   | X          | Ändern eines Gebäudes             |
| /api/buildings/{id: int} | DELETE    |            | X          | Löscht ein Gebäude                |

Beispiel Building:

```json
{
    "id": 1,
    "name": "SHL",
}
```

### Stockwerke

| URL                   | HTTP Verb | Parameters      | Authorized | Bedeutung                                     |
| --------------------- | --------- | --------------- | ---------- | --------------------------------------------- |
| /api/floors/{id: int} | GET       |                 | X          | Liefert eine Stockwerk anhand der ID          |
| /api/floors           | GET       | buildingId: int | X          | Liefert alle Stockwerke anhand der Gebäude ID |
| /api/floors           | POST      | Floor           | X          | Legt einen neuens Stockwerk an                |
| /api/floors/{id: int} | PUT       | Floor           | X          | Ändern eines Stockwerks                       |
| /api/floors/{id: int} | DELETE    |                 | X          | Löscht ein Stockwerk                          |

Beispiel Floor:

```json
{
    "id": 1,
    "name": "1. Stock",
    "buildingId" 1
}
```

### Räume

| URL                  | HTTP Verb | Parameters   | Authorized | Bedeutung                                  |
| -------------------- | --------- | ------------ | ---------- | ------------------------------------------ |
| /api/rooms/{id: int} | GET       |              | X          | Liefert einen Raum anhand der ID           |
| /api/rooms           | GET       | floorId: int | X          | Liefert alle Räume anhand der Stockwerk ID |
| /api/rooms           | POST      | Room         | X          | Erstellt einen neuen Raum                  |
| /api/rooms/{id: int} | PUT       | Room         | X          | Ändern eines Raums                         |
| /api/rooms/{id: int} | DELETE    |              | X          | Löscht einen Raum                          |

Beispiel Room:

```json
{
    "id": 1,
    "name": "H.1.1",
    "maxPersonCount": 20,
    "posX": 0,
    "posY": 0,
    "width": 13,
    "height": 20,
    "ioTDeviceId": "213213ddqwf31432wf",
    "floorId" 1
}
```

### IoT-Device

| URL                       | HTTP Verb | Parameters | Authorized | Bedeutung                                                            |
| ------------------------- | --------- | ---------- | ---------- | -------------------------------------------------------------------- |
| /api/iotDevices           | GET       |            | X          | Gibt alle IoT-Devices des aktuellen Benutzers zurück                 |
| /api/iotDevices/unused    | GET       |            | X          | Gibt alle nicht benutzten IoT-Devices des aktuellen Benutzers zurück |
| /api/iotDevices/{id: int} | PUT       |            | X          | Weißt das übergebene IoT-Device dem Benutzer zu                      |

### Belegungen

| URL                       | HTTP Verb | Parameters                        | Authorized | Bedeutung                               |
| ------------------------- | --------- | --------------------------------- | ---------- | --------------------------------------- |
| /api/occupations/history/ | GET       | roomId: int, from: Date, to: Date | X          | Ruft Historiendaten ab                  |
| /api/occupations/current  | GET       | roomId: int                       | X          | Gibt die aktuelle Personenanzahl zurück |

## Websockets

Alle Websocket Transaktionen sind Authorized. Dies bedeutet, dass sich der Client vor deren Benutzung über die HTTP WebAPI einloggen muss.

### Frontend -> Server

#### Abbonieren von Räumen

Hierzu wird ein Json Array von roomIDs an den Server gesendet.

Beispiel:

```json
[1, 2, 3]
```

Wird versucht Räume zu abonnieren, welche nicht dem eingeloggten Benutzer gehören oder ungültig sind wird die Verbindung getrennt.

### Server -> Frontend

#### Über Personenanzahl benachrichtigen

Hier wird ein Json Object mit roomID und aktueller Personen Anzahl an das Frontend gesendet.

Beispiel:

```json
{
    "roomId": 1,
    "personCount": 20
}
```