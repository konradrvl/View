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