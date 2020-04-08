# Shared

Shared beinhaltet Klassen und Interfaces die über das ganze Projekt hinweg genutzt und referenziert werden.

## Data

Data beinhaltet die Datenklassen die zur Generierung der Datenbank und zum Transport von Daten verwendet werden.

<img src="/img/server/Dependencies Graph Shared Data.png">

```C#
public class Building
{
    public int Id { get; set; }
    
    public string Name { get; set; }
    
    [JsonIgnore]
    public List<Floor> Floors { get; set; }

    [JsonIgnore]
    public int UserId { get; set; }
    
    [JsonIgnore]
    public User User { get; set; }
}
```

## Data Access

Interfaces für Data Access Klassen.

<img src="/img/server/Dependencies Graph Shared DataAccess.png">

## IoT Access

Interfaces für IoTAccess.

<img src="/img/server/Dependencies Graph Shared IoTAccess.png">

## Services

Interfaces für die Services.

<img src="/img/server/Dependencies Graph Shared Services.png">
