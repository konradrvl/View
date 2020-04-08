# Testszenarien für die Edit-Room Komponente

## User ändert nichts an den Daten des Raumes

1. User gibt keine neuen Daten ein und drückt den Edit Button.
> 1. Snackbar erscheint und benachrichtigt den User, dass der Raum richtig editiert wurde.
> 2. User wird auf die Chartansicht des Raumes weitergeleitet.

## User ändert die Daten des Raumes

User ändert Daten des Raumes, indem er in den Eingabefeldern neue Werte eingibt.

### Eingegebene Daten sind invalide

1. User gibt bei der maximalen Personenanzahl einen Text ein.
> 1. Form wird invalide und damit der Edit Button ausgegraut und deaktiviert.

### Eingegebene Daten sind valide

1. User gibt Änderungen ein, die Sinn machen.
2. User drückt den Edit Button.
> 1. Snackbar erscheint und benachrichtigt den User, dass der Raum richtig editiert wurde.
> 2. User wird auf die Chartansicht des Raumes weitergeleitet.