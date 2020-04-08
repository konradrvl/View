# Testszenarien für die Core-Komponente

## Ausfall Server

1. Netzwerkverbindung besteht
1. Verbindung zum Server bricht ab
> 1. Versuch mit dem Server zu Verbinden bis Verbindung erfolgreich ist

## Ausfall Netzwerkverbindung

1. Netzwerkverbindung bricht ab
> 1. Versuch mit dem Server zu Verbinden bis Verbindung erfolgreich ist

## Ausfall mit Netzwerkkonfiguration

1. Absturz und Neustart der Software
1. gültige Netzwerkkonfiguration (`disableWifiConnect == true`)
> 1. Versuch mit dem Server zu Verbinden bis Verbindung erfolgreich ist

## Ausfall ohne Netzwerkkonfiguration (AP-Modus)

1. Absturz und Neustart der Software
1. keine gültige Netzwerkkonfiguration (`disableWifiConnect == false`)
> 1. AP-Modus wird gestartet