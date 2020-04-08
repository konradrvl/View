# Architektur

Die Architektur des **IoT-Device** lässt sich durch die folgenden 4 einzelnen Komponenten beschreiben:

| Titel          | Beschreibung                                                                               |
| -------------- | ------------------------------------------------------------------------------------------ |
| core           | Führt die Personenerkennung durch und stellt eine Verbindung zum Server bereit.           |
| wifi-connector | Öffnet einen Wlan Hotspot und stellt die Konfigurationsoberfläche zur Verfügung.           |
| util           | Hilfsfunktionen zum einlesen und schreiben der Konfigurationsdatei (`configuration.json`). |
| main           | Einstiegspunkt in die Anwendung.                                                           |

Die folgende Grafik zeigt die Struktur:

<img class="diagram" src="/img/iot/iot_dependency_graph.svg">

Im folgenden werden die beiden wichtigen Module `core` und `wifi-connector` beschrieben.