# Architektur

View besteht aus 3 Hauptkomponenten:

* IoT-Device
* Server
* Frontend

Die **IoT-Devices** erfassen die Anzahl der Personen in Räumen und geben diese Werte an den zentralen **Server** weiter. Die Kommunikation erfolgt über Websockets.

Der **Server** speichert die Daten in einer Datenbank zur Anzeige der Historie und reicht sie an die verschiedenen Clients weiter.

Das **Frontend** besteht aus einer **Webapplikation**, welche die Daten aufbereitet und dem Benutzer präsentiert. Für den eingeloggten Benutzer ist außerdem das Anlegen und Verwalten von Räumen, Stockwerken und Gebäuden möglich.
Außerdem gibt es ein **WiFi-Frontend** mit dem der Benutzer **IoT-Devices** im WLAN anmelden kann.

Die Struktur auf höchster Ebenen ist in folgender Grafik abgebildet:

<img id="architecture" src="/img/architecture.svg">