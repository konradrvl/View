# Server compilieren

Beim Server handelt es sich um ein eine in C# geschriebene Anwendung. Das Programm benutzt das .Net Core Framework.

## Voraussetzungen

Die Server ist plattformunabhängig und läuft auf allen Plattformen, welche .Net Core unterstützen.

### Framework

+ [.Net Core 2.1](https://github.com/dotnet/core)

### Bibliotheken

+ [Asp.Net Core](https://github.com/aspnet/Home)
+ [Entity Framework Core](https://github.com/aspnet/EntityFrameworkCore)
+ [Fleck](https://github.com/statianzo/Fleck)
+ [Newtonsoft.Json](https://www.newtonsoft.com/json)

Die Bibliotheken werden beim bauen über automatisch Nuget hinzugefügt.

## Compilieren

Im Ordner server/View.Server.WebAPI:

+ `dotnet restore`
+ `dotnet build`
