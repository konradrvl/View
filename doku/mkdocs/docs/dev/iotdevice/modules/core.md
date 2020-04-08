# Core

Die `core` Komponente hat folgende Aufgaben:

* Personenerkennung
* Verbindung zum Server

## Personenerkennung

Die Personenerkennung basiert auf dem Deep Learning Model [YOLO](https://pjreddie.com/darknet/yolo/).
Dieses ermöglicht, selbst auf embedded Systemen, eine performante und zuverlässige Erkennung verschiedenster Objekte.

Zum Einspeisen des Videostreams in das neuronale Netz wird [OpenCV](https://opencv.org/) verwendet.

## Verbindung zum Server

Die Verbindung zum **Server** erfolgt über eine Websocket Schnittstelle. Diese ermöglicht eine einfache bidirektionale Verbindung.

## Klassen

Die folgende Grafik zeigt die wichtigsten Klassen im `core` Modul:

<img class="diagram" src="/img/iot/iot_core.svg">

### IotClient

Die Klasse `IotClient` erstellt Instanzen von `WebsocketConnection` und `Detection` und steuert deren Zustände.

Die `Detection` wird dabei erst nach erfolgreicher Verbindung von der `WebsocketConnection` zum **Server** gestartet. Bricht diese Verbindung ab, wird auch die `Detection` gestoppt.

Außerdem wird in dieser Klasse die aktuell erkannte Personenanzahl gespeichert und bei einer Veränderung `WebsocketConnection` benachrichtigt.

### WebsocketConnection

Die `WebsocketConnection` versucht wiederholt eine Verbindung zum **Sever** herzustellen.
Bei erfolgreicher Verbindung authentifiziert sich das Gerät mit seiner eindeutigen ID beim Server und sendet die aktuelle Personenanzahl.

Die Kommunikation wird [hier](/dev/interfaces/iotDeviceServer.md) beschrieben.

### Detection

Die `Detection` benutzt YOLO und OpenCV um Objekte zu erkennen. Daraus wird die Anzahl von Personen im beobachteten Raum bestimmt.

Dieser Prozess läuft auf 2 Threads:

1. `readFrames` holt von einer angeschlossenen Kamera die aktuellen Bilder und speichert die Frames.
2. `runRecognition` führt mit dem aktuellen Bild die YOLO Objekterkennung aus und erhält dadurch die Personenanzahl. Diese wird dann an `IotClient` mittels eines `boost::siganls2::signal` nach oben gegeben.

Diese Aufteilung ist notwendig, da die Objekterkennung ein relativ zeitaufwändiger Prozess ist und die Kamera Frames buffert. Dies würde bei sequenzieller Ausführung zum abruf veralteter Bilder führen.