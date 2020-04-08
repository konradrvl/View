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