# Testszenarien für die AddFloor Komponente

## User gibt nichts ein

1. User macht keine Eingabe in der Eingabemaske.
> 1. Add ist ausgegraut und es kann nichts an den Server abgesendet werden.

## User gibt Daten ein

### Eingegebene Daten sind ungültig

1. User gibt Daten in Eingabemaske ein, die nicht so vorgesehen sind. z.B. Einen String in das Feld `max. Persons`.
> 1. Formular zeigt in roter Schrift an, dass das Feld nicht valide ist.
> 2. Absenden des Formulars nicht möglich.

### Eingegebene Daten sind gültig

1. User gibt valide Daten in die Eingabemaske ein.
> 1. Add wird blau hinterlegt.
> 2. Formular kann abgesendet werden.

### Eingegebene Daten sind gültig und User verschiebt Raum

1. User gibt valide Daten in die Eingabemaske ein.
2. User vergrößert und/oder verschiebt den Raum.
> 1. Heatmap folgt den Mausbewegungen des Users und passt den Raum entsprechend an.
3. User drückt "Add" Button
> 1. Snackbar benachrichtigt User, dass der Raum erfolgreich erstellt wurde.
> 2. User wird auf die Chart-Ansicht des Raumes weitergeleitet, die bei einem neuen Raum leer ist.