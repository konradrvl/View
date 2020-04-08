# View

## Installation

Die passenden Installationspakete können [hier](/downloads.md#IoT-Client) heruntergeladen werden.

Nach der Installation muss die Konfigurationsdatei `configuration.json` angepasst werden.

## Konfiguration

Pfad zur Konfigurationsdatei:

* Linux: `/usr/share/view-iot-client/configuration.json`
* Windows: `C:/Program Files/view-iot-client/configuration.json`

Die Konfigurationsdatei nutzt das JSON Format. Genauere Informationen sind im [Handbuch](manual/person-detector.md#Konfiguration) zu finden.

Einige Beispielkonfigurationen:

### Beispielkonfiguration Linux ARMv7

```json
{
  "url": "ws://theprojectview.com:4711",
  "serialNumber": "1",
  "cfg": "data/cfg/yolov2.cfg",
  "weights": "data/yolov2.weights",
  "names": "data/data/coco.names",
  "threshold": 0.6,
  "cameraDevice": 0,
  "httpPort": 8080,
  "httpRoot": "web",
  "disableWifiConnect": false,
  "disableAP": false,
  "enableVideoOutput" : false
}
```

### Beispielkonfiguration Linux AMD64

```json
{
  "url": "ws://theprojectview.com:4711",
  "serialNumber": "1",
  "cfg": "data/cfg/yolov2.cfg",
  "weights": "data/yolov2.weights",
  "names": "data/data/coco.names",
  "threshold": 0.6,
  "cameraDevice": 0,
  "httpPort": 8080,
  "httpRoot": "web",
  "disableWifiConnect": true,
  "disableAP": true,
  "enableVideoOutput" : false
}
```

> Achtung:
> Ohne die Option `disableWifiConnect` wird die aktuelle WLAN Konfiguration, sowie die Konfiguration der Dienste `dnsmasq` und `hostapd` überschrieben.

### Beispielkonfiguration Windows x64

```json
{
  "url": "ws://theprojectview.com:4711",
  "serialNumber": "1",
  "cfg": "data/cfg/yolov2.cfg",
  "weights": "data/yolov2.weights",
  "names": "data/data/coco.names",
  "threshold": 0.6,
  "cameraDevice": 0,
  "enableVideoOutput": false
}
```

## Starten

* Linux: `view-iot-client` ausführen
* Windows: `C:/Program Files/view-iot-client/view-iot-client.exe` ausführen