# Testszenarien für die Login Komponente

## Valide Nutzerdaten

1. Nutzerdaten die vorher registriert wurden, werden eingegeben.
2. Login Button wird gedrückt.
> 1. Ladebildschirm erscheint.
> 2. Snackbar mit Rückmeldung über Erfolgreichen Login erscheint.
> 3. User ist erfolgreich eingeloggt und kann weiter navigieren.

## Keine Nutzerdaten

1. Eingabefelder sind leer, Login Button ist ausgegraut.

## Falsche Nutzerdaten

1. User gibt Daten ein, die vorher nicht registriert wurden, oder das Passwort nicht dem der Datenbank entspricht.
2. Login Button wird betätigt.
> 1. Snackbar benachrichtigt User, dass Login nicht erfolgreich war.

## Nutzer möchte sich registrieren

1. Sobald über Register gehoverd wird, bekommt der "Register" Button eine andere Hintergrundfarbe.
2. User drückt auf den Register Button.
3. User wird auf Register Seite weitergeleitet.