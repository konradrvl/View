# Server

## Voraussetzungen

Zum Speichern der Konfiguration und der Raumbelegungsdaten wird eine (leere) MySQL - Datenbank benötigt.

## Konfiguration

Die Konfigurationsdatei `Appsettings.json` liegt neben der Applikation.

Die Konfigurationsdatei ist im JSON Format geschrieben und umfasst folgende Optionen:

| Option | Erklärung | default |
| ------ | ------ | ------ |
| database | Datenbank-Connectionstring:</br>Server=[ip]:[port];</br>Database=[Datenbankname];</br>Uid=[User];</br>Pwd=[Passwort]; | `Server=localhost;Database=view;Uid=root;Pwd=toor;` |
| clientApi | IP & Port unter dem die Clientschnittstelle läuft | `http://0.0.0.0:4000` |
| detectorApi | IP & Port unter dem die Websocketschnittstelle für den Person detector läuft | `ws://0.0.0.0:4711` |
