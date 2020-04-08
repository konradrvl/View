# Testszenarien für die Room Komponente

## Raum löschen wird gedrückt

1. Nutzer drückt den "Löschen" Button.
> 1. User wird auf die Flooransicht zurückgeleitet.
> 2. Snackbar erscheint und benachrichtigt User über den erfolgreich gelöschten Raum.

## Raum wird editiert

1. User drückt auf den Stift Button.
> 1. User wird zum editieren des Raums weitergeleitet.

## Keine Raumbelegungswerte innerhalb der letzten 24 Stunden

Wurden in den letzten 24 Stunden keine Daten von einem IOTDevice an den Server gesendet, zeigt das Säulendiagramm keine Daten an. Es wird ein leeres Diagramm angezeigt.

## Daten der letzten 24 Stunden vorhanden

Es wird ein Säulendiagramm mit den Daten der letzten 24 Stunden angezeigt. Sind Fehlerwerte der Kamera vorhanden, so werden diese Daten mit einem grauen Balken visualisiert. Normale Personendaten sind hellblau eingefärbt.