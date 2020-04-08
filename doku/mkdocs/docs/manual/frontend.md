# Frontend Handbuch

## Login

Die Loginseite der Anwendung, hier kann sich mit Nutzername und Passwort angemeldet werden.
Wenn kein Benutzerkonto besteht kann zur Registrieren Seite navigiert werden.
Mit dem Feld **Keep me logged in!** kann entschieden werden ob man angemeldet bleiben möchte.

## Register

Die Registrierungsseite der Anwendung, hier kann sich registriert werden.

## Navigation

<img class="frontend-image" src="/gif/drawerexpand.gif">

Die Navigation findet über einen sogenannten **Drawer** statt, welcher sich auf der linken Bildschirmseite befindet.
Wenn die Mindestbreite des Bildschirms unterschritten wird, fährt sich der **Drawer** ein und kann über
den **Toolbar** wieder ausgefahren werden.

Über den mittleren Teil des Menüs erfolgt die Navigation durch Gebäude, Stockwerke und Räume. Die Unterüberschrift dient dabei
die Navigation nach "oben".

## Home

Die Landingpage der Anwendung.

## Building

<img class="frontend-image" src="/gif/building.png">

Hier werden alle Stockwerke eines Gebäudes angezeigt. Zu jedem Stockwerk werden auch die zugehörigen Räume und deren Belegung sofern verfügbar
**live** angezeigt.

## Floor

<img class="frontend-image-big" src="/gif/floor.png">

Hier werden alle Räume eines Stockwerks in einer **Heatmap** angezeigt. Die Räume zeigen die **Livedaten** durch Farbänderung auf der Heatmap und durch ein Zahlenlabel an.

## Room

<img class="frontend-image-big" src="/gif/room.png">

Hier wird eine Historie der Raumbelegung angezeigt. Falls Daten für diesen Raum für eine gewisse Zeit nicht erfasst wurden,
wird ein grauer Indikator angezeigt.

## Add

Hier können neue Elemente(Gebäude, Stockwerke, Räume oder IoT-Geräte) hinzugefügt werden. Diese Funktion ist im **Drawer** unter den aktuellen
Gebäuden, Stockwerken oder Räumen zu finden. Nur das Hinzufügen eines IoT-Geräts ist immer sichtbar.

## Edit

<img class="frontend-image-big" src="/gif/editfloor.gif">

Hier können Elemente(Gebäude, Stockwerke und Räume) bearbeitet werden. Diese Funktion ist in den Komponenten von
Gebäuden, Stockwerken oder Räumen zu finden.

## Delete

Gebäude, Stockwerke und Räume können in den jeweiligen Komponenten **kaskadierend** gelöscht werden.

## Settings

<img class="frontend-image" src="/gif/themeswitch.gif">

Im Einstellungsmenü lässt sich das **Theme** der Anwendung einstellen.

## WiFi-Frontend

Diese Oberfläche ist durch das Verbinden zu einem **IoT-Device** erreichbar. Hier kann das **IoT-Device** durch Auswahl eines
Netzwerkes und ggf. durch die Eingabe eines Passworts mit einem WLAN-Netzwerk verbunden werden.