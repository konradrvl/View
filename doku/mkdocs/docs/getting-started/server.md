# Server

## Installation

Die passenden Installationspakete können [hier](/downloads.md#Server) heruntergeladen werden.

Nach der Installation muss die Konfigurationsdatei `appsettings.json` angepasst werden.

## Konfiguration

Die Konfigurationsdatei `Appsettings.json` liegt neben der Applikation.

Es wird das JSON Format genutzt. Genauere Informationen sind im [Handbuch](manual/server.md#Konfiguration) zu finden.

Standartmäßig sind die IoT-Device ID's 1-10 in der Datenbank eingetragen. Weitere ID's müssen manuell in die Datenbank eingetragen werden.

### Beispielkonfiguration

```json
{
  "database": "Server=localhost;Database=view;Uid=root;Pwd=toor;",
  "clientApi": "http://0.0.0.0:4000",
  "detectorApi": "ws://0.0.0.0:4711"
}
```

## Starten

* Linux: `view-server` ausführen
* Windows: `view-server.exe` ausführen