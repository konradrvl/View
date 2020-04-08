# Person detector

> Hinweis: Unter Windows sind sämtliche WLAN-Funktionalitäten deaktiviert.

## Konfiguration

Pfad zur Konfigurationsdatei:

* Linux: `/usr/share/view-iot-client/configuration.json`
* Windows: `C:/Program Files/view-iot-client/configuration.json`

Die Konfigurationsdatei ist im JSON Format geschrieben und umfasst folgende Optionen:

| Option | Erklärung | default |
| ------ | ------ | ------ |
| url | Websocketadresse des Servers | `ws://localhost:4711` |
| serialNumber | Einzigartige ID des Geräts | `1` |
| cfg | Pfad der Konfigurationsdatei für YOLO | `data/cfg/yolov2.cfg` |
| weights | Pfad der Gewichte für YOLO | `data/cfg/yolov2.weights` |
| names | Pfad der `names` Datei für YOLO | `data/data/coco.names` |
| threshold | Wert für die Empfindlichkeit der Personenerkennung.</br> Zu niedrige Werte führen u.U. zu false postives und zu </br> hohe Werte zu false negatives (Wertebereich 0 - 1) | `0.6` |
| cameraDevice | Parameter zum Auswählen der Kamera für OpenCV | `0` |
| httpPort | Port für die Weboberfläche zur WLAN-Konfiguration (Unter Windows ignoriert) | `8080` |
| httpRoot | Verzeichnis der Weboberfläche der WLAN-Konfiguration (Unter Windows ignoriert) | `web` |
| disableWifiConnect | Deaktiviert Verbindungsprüfung, WLAN-Hotspot und WLAN-Konfigurationsoberfläche </br> (Wird zum Zurücksetzen der Netzwerkkonfiguration genutzt; Unter Windows ignoriert) | `false` |

optionale Parameter:

| Option | Erklärung | default |
| ------ | ------ | ------ |
| disableAP | Deaktiviert den WLAN-AP (Unter Windows nicht genutzt) | nicht gesetzt |
| enableVideoOutput | Aktiviert die Anzeige des aktuellen Videobildes mit Boundingboxen </br> Nicht unterstützt unter ARMv7 | nicht gesetzt |

## Dienst

Bei der Installation des DEB-Pakets wird ein Dienst mitinstalliert. Somit ist ein Start des Programms bei Systemstart möglich. Dazu muss der Dienst `view-iot-client` aktiviert werden.
Auch das Starten und Beenden des Programms ist mit Hilfe des Dienstes möglich:

* Autostart aktivieren: `systemctl enable view-iot-client`
* Dienst starten: `systemctl start view-iot-client`
* Dienst beenden: `systemctl stop view-iot-client`