# Testszenarien für das Stockwerks Komponente

## Stockwerk löschen wird gedrückt

1. Nutzer betätigt den "Löschen" Button.
> 2. User wird auf die Heatmapseite zurückgeleitet.
> 3. Snackbar erscheint und benachrichtigt User über das erfolgreich gelöschte Stockwerk.

## Stockwerk wird editiert

1. User drückt auf den Stift Button.
> 2. User wird zum editieren des Stockwerks weitergeleitet.

## Stockwerk hat keine Räume

Hat das Stockwerk keine Räume, so bleibt wird ein weißes Fenster ohne Inhalt angezeigt.

## Stockwerk hat Räume

Hat das Stockwerk Räume, so wird eine Heatmap angezeigt, diese zeigt die Größe der Räume sowie deren Position und die Namen der Räume.

### Raum hat keine/offline Kamera

Ist keine Kamera angeschlossen oder ist offline, so wird eine blaue durchgestrichene Kamera mittig unterhalb des Raumnamen`s angezeigt.

### Raum hat angeschlossene Kamera die Daten sendet

Unterhalb des Raumnamens wird die Anzahl der aktuellen Personen angezeigt mit der Information, wie viele Personen maximal in der Raum passen in der Form *ist/max*. Außerdem wird anhand der Belegung des Raums die Hintergrundfarbe des Raumes angepasst. Befinden sich keine Personen im Raum, bleibt die Hintergrundfarbe grau.