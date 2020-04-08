# Testszenarien für die Navigation-Bar Komponente

## Genereller Aufbau

Unabhängig von der Position an der sich der User gerade befindet, werden einige Standardelemente angezeigt. Dazu zählen:

* Home: Bei klick wird der User auf die Home Ansicht geleitet.
* AddIoTDevice: Ruft die Registrierung von IoTDevices auf.
* Settings: Ruft die Einstellungen des Frontends auf.
* Help: Ruft die Hilfeseite des Frontends auf.

## Ansicht mit kleinem Fenster oder auf mobilem Endgerät

Ist das das Browserfenster unter einer bestimmten Größe, wird die Navigation Bar eingeklappt und kann durch das Menü Symbol oben links ausgeklappt werden.

## Ansicht mit großem Fenster

Navigation Bar ist standardmäßig ausgeklappt und ist fester Bestandteil der Applikation.

## Fenstergröße wird verändert

1. User verkleinert/vergrößert das Fenster.
> 1. Navigation bar klappt sich automatisch aus bzw. ein.

## Home Ansicht / Kein Gebäude ausgewählt

Titel der Auflistung lautet "BUILDINGS". Darunter werden in einer Liste die vorher angelegten Gebäude angezeigt. Sind vorher keine Gebäude angelegt worden, so ist die Liste leer und es wird lediglich die Option zum hinzufügen eines Gebäudes angezeigt. Diese wird auch angezeigt, wenn Gebäude vorhanden sind. Wird eines der Gebäude angewählt, ändert sich die Ansicht zum nächsten Punkt (Gebäude Ansicht).

## Gebäude Ansicht / Gebäude wurde ausgewählt

Titel der Auflistung lautet "BUILDING". Statt Gebäuden werden jetzt Stockwerke angezeigt. Ansonsten muss sich die Ansicht genauso verhalten wie die Home Ansicht, bei der die Gebäude angezeigt werden. Statt Gebäuden anlegen kann man dementsprechend hier Stockwerke hinzufügen.

## Stockwerk Ansicht / Stockwerk wurde ausgewählt

Titel der Auflistung lautet "FLOOR". Analog zu Gebäude Ansicht werden die Räume des Stockwerks aufgelistet. Statt Stockwerken kann ein Raum hinzugefügt werden. Wird ein Raum ausgewählt bleibt die Ansicht im Prinzip bis auf den Titel der Auflistung gleich. Der Titel lautet dann "ROOM".