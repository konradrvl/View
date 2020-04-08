# Architektur

Die Architektur des **Servers** lässt sich durch die folgenden 5 einzelnen Komponenten beschreiben:

| Titel          | Beschreibung                                                                               |
| -------------- | ------------------------------------------------------------------------------------------ |
| DbAccess       | Stellt eine Verbindung zur Datenbank bereit.                                               |
| Service        | Verwaltet die Kommunikation zwischen Schnittstellenkomponenten                             |
| Shared         | Allgemeine Ressourcen(z.B. Interfaces, Datenklassen).                                      |
| WebAPI         | Einstiegspunkt in die Anwendung, liefert die **Webapplikation** aus.                       |
| WsIoTAccess    | Schnittstelle zur Kommunikation mit den **IoT-Devices** .                                  |

Für den **Server** wird [.NET Core](https://github.com/dotnet/core) mit den Erweiterungen [Entity Framework Core](https://docs.microsoft.com/de-de/ef/core/) und [ASP.NET Core](https://docs.microsoft.com/de-de/aspnet/core/?view=aspnetcore-2.1) als Framework eingesetzt. Das Entity Framework bietet dabei eine O/RM Funktion die den Zugriff auf eine MySQL Datenbank ohne prepared Statements ermöglicht. Die Datenbank wird nach dem "code first" Prinzip erzeugt. ASP.NET liefert das Usermanagement System,
das Sessionhandling, Authentifikation und Passworthashing. Das ASP.NET Framework bietet außerdem Dependency-Injection, worauf der gesamte Server aufbaut. Dadurch lässt sich die komplette Serverarchitektur voneinander entkoppeln.
<img class="diagram" src="/img/server/server dependency graph.svg">