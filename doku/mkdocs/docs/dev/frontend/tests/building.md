# Testszenarien für die Building-Komponente

## Gebäude löschen wird gedrückt

1. Nutzer betätigt den "Löschen" Button.
> 2. User wird auf Homeseite zurückgeleitet.
> 3. Snackbar erscheint und benachrichtigt User über das erfolgreich gelöschte Gebäude.

## Gebäude wird editiert

1. User drückt auf den Stift Button.
> 2. User wird zum editieren des Gebäudes weitergeleitet.

## Gebäude ohne Stockwerke

Hat ein Gebäude keine Stockwerke, so kann es auch keine Räume angezeigt. Deshalb wird in diesem Fall nichts angezeigt.

## Stockwerke ohne Räume

Sind nur Stockwerke und keine Räume angelegt, so werden auch nur die Titelzeilen der jeweiligen Stockwerke angezeigt. Die Titelzeilen beinhalten dabei die Namen also den Titel des jeweiligen Stockwerks.

## Stockwerke mit Räumen

Sobald Stockwerke einen bis mehrere Räume haben, werden die Räume in einer Liste angeordnet unter der Titelleiste angezeigt. Die Zeile beginnt mit einem statischen Symbol sowie dem Namen des Raumes.

### Raum ohne Kamera

Ist dem Raum kein IOTDevice zugeordnet oder nicht angeschaltet, so erscheint an dem rechten Rand der Zeile eine durchgestrichene Kamera.

### Raum mit Kamera

Sobald ein Raum ein IOTDevice besitzt und dieses Daten sendet, wird das durchgestrichene Kamerasymbol mit einer *ist/max* Anzahl und einer Person rechts daneben ersetzt. Beispielsweise 1/20 und das Personensymbol.