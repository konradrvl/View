# WiFi-Frontend -> IoT-Device

Die Kommunikation zwischen WiFi-Frontend und IoT-Device erfolgt über ein HTTP WebAPI.

Folgende Aufrufe sind möglich:

| URL       | HTTP Verb | Parameters        | Antwort      | Bedeutung                                |
| --------- | --------- | ----------------- | ------------ | ---------------------------------------- |
| /api/wifi | GET       |                   | WifiResponce | Abfragen der verfügbaren WiFi Netzwerken |
| /api/wifi | PUT       | WifiConnectParams |              | Verbinden mit einem WiFi Netzwerk        |

Beispiel WifiConnectParams:

```json
{
    "ssid": "Fritz!Box 1234",
    "passwd": "SuperSicheresPasswort2"
}
```

Beispiel WifiResponce:

```json
[
    {
        "ssid": "Fritz!Box 1234",
        "quality": 4,
        "encrypted": true
    }
]
```