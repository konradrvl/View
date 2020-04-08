# Testszenarien für die Edit-Floor Komponente

## User ändert nichts

1. User gibt nichts ein und drückt nur auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.

## User ändert den Namen des Stockwerks

1. User gibt im Feld für den Namen des Stockwerks einen neuen String ein.
2. User drückt auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.

## User verschiebt Räume

1. User verschiebt Räume per Drag & Drop.
2. User drückt auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.
> 3. Raum wird an der verschobenen Stelle auf der Heatmap angezeigt.

## User vergrößert bzw. verkleinert Raum

1. User vergrößert den Raum, indem er entweder an den jeweiligen Seiten die Maus gedrückt hält, bis der Raum die gewünschte Größe hat oder anhand der kleinen Ecke unten rechts, um Breite und Höhe gleichzeitig zu verändern.
2. User drückt auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.
> 3. Raum wird in der neuen Größe auf der Heatmap angezeigt.

## User verschiebt und verändert die Größe eines Raumes

1. User vergrößert den Raum und verschiebt ihn wie bereits beschrieben.
2. User drückt auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.
> 3. Raum wird in der neuen Größe  und an der neuen Stelle auf der Heatmap angezeigt.

## User verschiebt und verändert die Größe mehrere Räume

1. User wiederholt den Vorgang mit vergrößern und verschieben mit beliebig vielen Räumen.
2. User drückt auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.
> 3. Raum wird in der neuen Größe  und an der neuen Stelle auf der Heatmap angezeigt.

## User vergrößert und verschiebt mehrere Räume und ändert den Namen des Stockwerks

1. User verschiebt und ändert die Größe mehrerer Räume.
2. User ändert den Namen des Stockwerks.
3. User drückt auf Edit.
> 1. Snackbar erscheint und benachrichtigt User, dass das Stockwerk editiert wurde.
> 2. User wird auf die Stockwerksansicht (Heatmap) weitergeleitet.
> 3. Raum wird in der neuen Größe  und an der neuen Stelle auf der Heatmap angezeigt.
> 4. Stockwerk hat den neuen Namen.