# Testszenarien für das WiFi-Frontend

## Starten des IoT-Device ohne Netzwerkkonfiguration

1. Software startet ohne Netzwerkkonfiguration (`disableWifiConnect == false`)
> 1. AP-Modus wird gestartet

## Starten des IoT-Device ohne Netzwerkkonfiguration mit Ethernetverbindung

1. Software startet ohne Netzwerkkonfiguration (`disableWifiConnect == false`)
1. Kabelnetzwerkverbindung ist verfügbar
> 1. `disableWifiConnect == true` wird gesetzt
> 1. Detection-Modus wird gestartet

## Starten des IoT-Device mit Netzwerkkonfiguration und fehlender Verbindung

1. Software startet mit Netzwerkkonfiguration (`disableWifiConnect == true`)
1. fehlende Netzwerkverbindung
> 1. Versuch mit dem Server zu Verbinden bis Verbindung erfolgreich ist

## Starten des IoT-Device mit Netzwerkkonfiguration mit Netzwerkverbindung

1. Software startet mit Netzwerkkonfiguration (`disableWifiConnect == true`)
1. Netzwerkverbindung besteht
> 1. Versuch mit dem Server zu Verbinden bis Verbindung erfolgreich ist

## WLAN-Konfiguration mit richtigen Zugangsdaten

1. Nutzer wählt WLAN Netzwerk in der Weboberfläche aus
1. Nutzer gibt richtiges Passwort ein
> 1. AP wird gestoppt
> 1. DNS & DHCP Server werden gestoppt
> 1. Firewall-Regeln werden zurückgesetzt
> 1. WLAN Zugangsdaten werden in die Konfigurationsdatei eingetragen
> 1. Netzwerkverbindung wird hergestellt
> 1.`disableWifiConnect == true` wird gesetzt
> 1. HTTP Server wird gestoppt
> 1. Versuch mit dem Server zu Verbinden bis Verbindung erfolgreich ist

## WLAN-Konfiguration mit falschen Zugangsdaten

1. Nutzer wählt WLAN Netzwerk in der Weboberfläche aus
1. Nutzer gibt falsches Passwort ein
> 1. AP wird gestoppt
> 1. DNS & DHCP Server werden gestoppt
> 1. Firewall-Regeln werden zurückgesetzt
> 1. WLAN Zugangsdaten werden in die Konfigurationsdatei eingetragen
> 1. Verbindungsherstellung schlägt fehl
> 1. AP-Modus wird wieder gestartet

## AP-Modus wird gestartet

1. AP wird durch Core Komponente gestartet
> 1. Firewall-Regeln werden gesetzt
> 1. AP wird gestartet
> 1. DNS & DHCP Server werden gestartet
> 1. HTTP Server für Weboberfläche wird gestartet