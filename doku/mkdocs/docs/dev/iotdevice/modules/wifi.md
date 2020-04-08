# WiFi-Connector

Die `WiFi-Connector` Komponente ist dafür zuständig einen WLAN Hotspot zu starten und eine Web-Konfigurationsoberfläche auszuliefern. Mit dieser hat der Benutzer die Möglichkeit das **Iot-Device** mit seinem WLAN Netzwerk zu verbinden.

Der `WiFi-Connector` benutzt dabei Linux Betriebssystem -befehle und -tools und ist daher nur unter Linux lauffähig.

## WiFi Hotspot und captive portal

Zum Ausliefern der Konfigurationsoberfläche wird vom Gerät ein WLAN Netzwerk aufgespannt. Durch das Captive Portal wird der Nutzer direkt beim Verbinden mit dem Netzwerk auf die Weboberfläche hingewiesen.

Das Captive Portal wird durch eine Kombination von Firewall-Regeln und Umleiten von DNS-Anfragen auf den eigenen Webserver [realisiert](#start_apsh).

<img class="frontend-image" src="/gif/captive_portal.gif">

## Webserver

Der [Webserver](#HttpServer) liefert das [WiFi-Frontend](Hier könnte Ihr link stehen.) aus. Der Webserver führt einen Redirect aller Anfragen (außer die API Zugriffe) an die index.html durch.

TODO: Link nach Wifi Frontend

## WiFi Verbindung herstellen

Das Verbinden mit einem WiFi Netzwerk erfolgt mithilfe eines eigens geschriebenen [bash scripts](#wifish).
Bei erfolgreicher Verbindung werde Webserver und Access Point gestoppt und das `core` Modul initialisiert.

## Klassen

Die folgende Grafik zeigt die wichtigsten Klassen im `WiFi-Connector` Modul:

<img class="diagram" src="/img/iot/iot_wificonnector.svg">

### WifiConnector

Der `WifiConnector` dient als zentrale Klasse im `wifi-connector` Modul. Hier werden die Konfigurationen der benötigten Dienste über den `LinuxSystemAccess` ausgelöst, WiFi Hotspot und Websever über `HttpServer` gestartet.

### LinuxSystemAccess

Der `LinuxSystemAccess` ist eine Reihe von statischen Hilfsmethoden, welche Zugriff auf das Betriebssystem bieten.

| Methode              | Beschreibung |
| -------------------- | ------------ |
| isRoot               | Nutzt den Befehl `id` um festzustellen, ob die Anwendung mit root Rechten gestartet wurde. |
| isConnected          | Nutzt den Befehl `ping` um festzustellen, ob de Rechner eine Standartgateway besitzt.|
| initHostApd          | Schreibt das configurationsfile für den Dienst `hostapd`.|
| initDns              | Schreibt das configurationsfile für den Dienst `dnsmask`.|
| setHostApdConfig     | Schreibt die daemon Konfiguration von `hostapd`.|
| connectWifi          | Ruft das script [wifi.sh](#wifish) auf.|
| getWifiList          | Benutzt den Befeh `iwlist scann` um eine Liste aller verfügbaren Wifi Netzwerke zu erhalten.|
| getWifiInterfaceName | Benutzt den Befehl `iw dev` um den Namen der erste Wifi Netzwerkschnittstelle zu ermitteln.|
| startAp               | Ruft das script [start_ap.sh](#start_apsh) auf.|
| stopAp                | Ruft das script [stop_ap.sh](#stop_apsh) auf.|

### IwlistScanParser

Der `IwlistScanParser` hat die Aufgabe die textuelle Ausgabe des `iwlist scann` Befehls zu verarbeiten. Der `IwlistScannParser` wird dabei in der Methode `getWifiList` vom `LinuxSystemAccess` verwendet.

Von `iwlist scann` wird jedes Netzwerk als `Cell` mit verschiedenen Parametern ausgegeben:

```
Cell 10 - Address: D8:84:66:4A:22:A4
                    Channel:40
                    Frequency:5.2 GHz (Channel 40)
                    Quality=61/70  Signal level=-49 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001bd531c0dcc2
                    Extra: Last beacon: 4556ms ago

```

Es werden nun nacheinander die benötigten Parameter herausgelesen.
Dies sind:

+ Quality
+ Enryption
+ ESSID
+ Authentication

Beispiel für die Bestimmung der Signalqualität in einer `Cell`:

```c++
void IwlistScanParser::findQuality(std::string &line) {
    if (!foundQuality && line.find("Quality=") != std::string::npos) {
        boost::algorithm::trim(line);
        // After trim we have something like: Quality=61/70 Signal level=-49 dBm

        auto pos = line.find_first_of('=');
        auto len = line.find_first_of(' ') - pos;
        auto qualityStr = line.substr(pos + 1, len);
        // After substr we have something like: 61/70

        std::vector<std::string> qualities;
        boost::split(qualities, qualityStr, boost::algorithm::is_any_of("/"));

        int currentQuality = std::stoi(qualities[0]);
        int maxQuality = std::stoi(qualities[1]);

        // We measure quality in only 4 levels
        quality = (int) std::round((((double) currentQuality) / maxQuality) * 4);
        foundQuality = true;
    }
}
```

### HTTP Server

Mithilfe der Bibliothek `cpp-httplib` wird ein HTTP Server erstellt. Es wird ein

+ GET zum abrufen der verfügbaren WiFi Netzwerke (ruft `getWifiList` im [LinuxSystemAccess](#LinuxSystemAccess) auf) und ein
+ PUT zum Herstellen einer Verbindung (ruft `connectWifi` im [LinuxSystemAccess](#LinuxSystemAccess) auf)

bereitgestellt.

Des weiteren werden alle anderen Anfragen auf die index.html des WiFi-Frontends weitergeleitet.

```c++
void HttpServer::start(int port, const std::string &httpRoot) {
    server.Get("/api/wifi", [&](const auto &req, auto &res) { this->onRequestedWifiList(req, res); });
    server.Put("/api/wifi", [&](const auto &req, auto &res) { this->onConnectWifi(req, res); });

    server.set_base_dir(httpRoot.c_str());

    server.Get(".*", [&](const auto &req, auto &res) { res.set_redirect("/"); });

    std::cout << "Starting http server on port " << port << std::endl;

    server.listen("0.0.0.0", port);

    std::cout << "Http server stopped" << std::endl;
}
```

## Scripte

### start_ap.sh

Dieses Script ist für das Konfigurieren des WiFi Hotspot und captive portal zuständig.
Mit `iptables` werden die Firewall konfigurationen für das captive portal gesetzt. Hierzu werden alle Anfragen an das Gerät an Port 80 (HTTP) und 443 (HTTPS) weitergeleitet.

Mit `ip address` werden die aktuellen Netzwerkeinstellungen zurückgesetzt und eine feste IP vergeben.

Anschließend wird mit `dnsmasq` der DNS und DHCP Server gestartet, welcher alle DNS Anfragen auf das eigene Gerät umleitet.

```bash
#!/bin/bash

apip="192.168.178.1"
netmask="24"
broadcast="192.168.178.255"
port="8080"
interface="$1"

dhcpcd="denyinterfaces $interface
"

# setup iptables
echo "Setting iptables"
iptables -t nat -F
iptables -t nat -A PREROUTING -p tcp --dport 80 -j DNAT  --to-destination  $apip:$port
iptables -t nat -A PREROUTING -p tcp --dport 443 -j DNAT --to-destination  $apip:$port

# edit dhcpcd config
echo "$dhcpcd" > /etc/dhcpcd.conf
systemctl restart dhcpcd

# disconnect from wifi & stop wpa_supplicant
killall wpa_supplicant

# set IP address
echo "Setting IP Address for $interface"
ip address flush dev $interface
ip address add $apip/$netmask broadcast $broadcast dev $interface
ip link set $interface up

# start AP
echo "Attempting to start hostapd"
systemctl restart hostapd

# start DHCP & DNS Server
echo "Attempting to start dnsmasq"
systemctl restart dnsmasq

# disable AP DNS autostart
systemctl disable hostapd
systemctl disable dnsmasq
```

### stop_ap.sh

Dieses Script stoppt die Dienste `hostapd` und `dnsmasq`. Des weiteren werden die `iptables` Regeln zurückgesetzt.

```bash
#!/bin/bash

# stop AP
echo "Attempting to stop hostapd"
systemctl stop hostapd

# stop DHCP & DNS Server
echo "Attempting to stop dnsmasq"
systemctl stop dnsmasq

# reset iptables
echo "Resetting iptables"
iptables -t nat -F
```

### wifi.sh

Dieses Script nimmt die 3 Parameter ssid, passwd, und wifi-interface entgegen, konfiguriert und startet den `wpa_supplicant`. Dieser stellt eine Verbindung zum WLAN Netzwerk her.

```bash
#! /bin/bash

apip="192.168.178.1"
interface="$3"

wpa_supplicant="ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
        ssid=\""$1"\"
        psk=\""$2"\"
}"

#dhcpcd="denyinterfaces eth0
#"

dhcpcd=""

# reset interface
ip address flush dev $interface

# edit wpa_supplicant config
echo "$wpa_supplicant" > /etc/wpa_supplicant/wpa_supplicant.conf

# edit dhcpcd config
echo "$dhcpcd" > /etc/dhcpcd.conf
systemctl restart dhcpcd

# update IP Adress & DNS Server from DHCP
dhclient -r $interface
dhclient $interface

```