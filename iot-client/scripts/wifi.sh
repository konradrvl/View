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
