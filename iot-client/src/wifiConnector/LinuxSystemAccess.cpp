//
// Created by julian on 14.05.18.
//

#include "LinuxSystemAccess.h"
#include "IwlistScanParser.h"
#include "exceptions/WifiInterfaceBusyExeption.h"

#include "../util/Util.h"

#include <pstream.h>

#include <boost/format.hpp>

#include <iostream>
#include <ios>
#include <fstream>
#include <chrono>
#include <thread>

bool LinuxSystemAccess::hasWirelessTools() {
    int result = std::system("iwlist -v > /dev/null 2>&1");

    return result == 0;
}

bool LinuxSystemAccess::isConnected() {
    // This command will finish with a zero exit code if there is a network connection
    int result = std::system("ping -q -w 1 -c 1 `ip r | grep default | cut -d ' ' -f 3` > /dev/null 2>&1");

    return result == 0;
}

bool LinuxSystemAccess::isRoot() {
    // If the application is started with root rights this will return 0
    auto erg = executeCmd("id -u");

    return erg[0] == "0";
}

void LinuxSystemAccess::initAp() {
    initHostApd();
    setHostApdConfig();
    initDns();
}

void LinuxSystemAccess::initHostApd() {
    std::ofstream ofs("/etc/hostapd/hostapd.conf", std::ofstream::out | std::ofstream::trunc);

    auto lines = std::vector<std::string> {
            "interface=" + getWifiInterfaceName(),
            "driver=nl80211",
            "ssid=ViewWifiAP",
            "channel=6",
            "hw_mode=g",
            "wmm_enabled=0"
    };


    for(const auto& line : lines) {
        ofs << line << "\n";
    }
}

void LinuxSystemAccess::setHostApdConfig() {
    std::vector<std::string> lines;

    {
        std::ifstream ifs("/etc/init.d/hostapd");

        std::string line;
        while (std::getline(ifs, line)) {
            lines.emplace_back(std::move(line));
        }
    }

    {
        std::ofstream ofs("/etc/init.d/hostapd");

        for(auto& line : lines) {
            if(line.find("DAEMON_CONF=") != std::string::npos) {
                line = "DAEMON_CONF=/etc/hostapd/hostapd.conf";
            }

            ofs << line << "\n";
        }
    }
}

void LinuxSystemAccess::initDns() {
    std::ofstream ofs("/etc/dnsmasq.conf", std::ofstream::out | std::ofstream::trunc);

    auto lines = std::vector<std::string> {
            "interface=" + getWifiInterfaceName(),
            "dhcp-range=192.168.178.2,192.168.178.200,255.255.255.0,24h",
            "address=/#/192.168.178.1"
    };

    for(const auto& line : lines) {
        ofs << line << "\n";
    }
}

bool LinuxSystemAccess::connectWifi(const std::string &ssid, const std::string &passwd) {
    if(!isRoot()) {
        std::cout << "Couldn't connect wifi without root!" << std::endl;
        return false;
    }

    auto script = Util::buildDataFilePath("scripts/wifi.sh");

    auto cmd = (boost::format(R"(%s "%s" "%s" "%s")") % script % ssid % passwd % getWifiInterfaceName()).str();

    std::cout << "Will connect to " << ssid << std::endl;

    LinuxSystemAccess::stopAp();
    executeCmd(cmd);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto success = isConnected();

    if(success) {
        std::cout << "Connected to " << ssid << std::endl;
    } else {
        std::cout << "Couldn't connect to " << ssid << std::endl;
    }

    return success;
}

std::vector<Wifi> LinuxSystemAccess::getWifiList() {
    auto lines = executeCmd("iwlist " + getWifiInterfaceName() + " scan 2>&1");

    checkIfInterfaceIsBusy(lines);

    IwlistScanParser parser;

    return parser.parse(lines);
}

bool LinuxSystemAccess::hasWifiInterface() {
    return !getWifiInterfaceName().empty();
}

std::string LinuxSystemAccess::getWifiInterfaceName() {
    auto iwPath = executeCmd("whereis iw | awk '$1==\"iw:\"{print $2}'")[0];
    auto erg = executeCmd(iwPath +  " dev | awk '$1==\"Interface\"{print $2}'");

    return erg[0];
}

bool LinuxSystemAccess::startAp() {
    if(isRoot()) {
        auto script = Util::buildDataFilePath("scripts/start_ap.sh");
        auto cmd = (boost::format("%s %s") % script % getWifiInterfaceName()).str();
        auto erg = executeCmd(cmd);

        return erg[0] == "0";
    } else {
        std::cout << "Couldn't start AP without root!" << std::endl;
        return false;
    }
}

void LinuxSystemAccess::stopAp() {
    if(isRoot()) {
        auto script = Util::buildDataFilePath("scripts/stop_ap.sh");
        auto erg = executeCmd(script);
    } else {
        std::cout << "Couldn't stop AP without root!" << std::endl;
    }
}

std::vector<std::string> LinuxSystemAccess::executeCmd(const std::string &cmd) {
    redi::ipstream is(cmd);

    std::vector<std::string> lines;

    std::string line;
    while (std::getline(is, line)) {
        lines.emplace_back(std::move(line));
    }

    return lines;
}

void LinuxSystemAccess::checkIfInterfaceIsBusy(const std::vector<std::string> &vector) {
    if(vector.size() == 2) {
        if(vector[0].find("Device or resource busy") != std::string::npos) {
            throw WifiInterfaceBusyExeption();
        }
    }
}
