# Architektur

<img class="material-icon" src="/img/Angular.png">

Das Frontend besteht aus 2 Modulen:

| Titel          | Beschreibung                                                                               |
| -------------- | ------------------------------------------------------------------------------------------ |
| Webapplikation | Stellt die Hauptanwendung des Kunden dar und wird vom **Server** ausgeliefert.             |
| WiFi-Frontend  | Frontend, das auf dem **IoT-Device** läuft um die WLAN Konfiguration zu erstellen.         |

In beiden Fällen wird [Angular 6](https://angular.io/) als Framework eingesetzt.
Dabei werden Typescript, HTML und CSS als Hauptsprachen für das Projekt verwendet.
In dieser Dokumentation wird auf die wichtigsten Komponenten und Services dieser Applikation eingegangen.
Es wird allerdings **nicht** die Projektstruktur und Funktionsweise von Angular erklärt.
