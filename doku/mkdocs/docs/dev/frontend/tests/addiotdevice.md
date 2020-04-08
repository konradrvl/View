# Testszenarien für die AddIoTDevice Komponente

## Keine Daten werden eingegeben

1. User befindet sich auf Komponente und hat bisher nichts eingegeben.
> 1. Button zum Hinzufügen eines IoTDevices ist ausgegraut und kann nicht betätigt werden.

## Seriennummer wird eingegeben

User gibt eine Seriennummer ein.

### Seriennummer ist gültig

Snackbar benachrichtigt User über die erfolgreiche Registrierung des IotDevices.

### Seriennummer ist ungültig

Snackbar benachrichtigt User, dass die Seriennummer ungültig ist und der Vorgang nicht erfolgreich abgeschlossen wurde.