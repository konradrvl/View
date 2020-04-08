//
// Created by julian on 24.05.18.
//

#include "IwlistScanParser.h"

#include <cmath>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

std::vector<Wifi> IwlistScanParser::parse(std::vector<std::string> &lines) {
    cell = 1;

    std::vector<Wifi> wifis;

    for (auto &line : lines) {
        findCell(line, wifis);
        findQuality(line);
        findEncrypted(line);
        findSsid(line);
        findAuthentication(line);
    }

    removeDuplicates(wifis);

    return wifis;
}

void IwlistScanParser::findCell(const std::string &line, std::vector<Wifi> &wifis) {
    auto cellStr = (boost::format(" Cell %02d - Address: ") % cell).str();
    if (line.find(cellStr) != std::string::npos) {
        if (foundSSid && foundEncrypted && foundQuality) {
            if (foundAuthentication && authentication == "PSK" || !encrypted) {
                if (!ssid.empty()) {
                    wifis.emplace_back(ssid, quality, encrypted);
                }
            }
        }

        cell++;

        foundSSid = false;
        foundEncrypted = false;
        foundQuality = false;
        foundAuthentication = false;
    }
}

void IwlistScanParser::findSsid(std::string &line) {
    if (!foundSSid && line.find("ESSID:") != std::string::npos) {
        boost::algorithm::trim(line);
        // After trim we have something like: ESSID:"Fritz!Box"

        auto pos = line.find_first_of('"');
        auto len = line.find_last_of('"') - pos;
        ssid = line.substr(pos + 1, len - 1);
        foundSSid = true;
    }
}

void IwlistScanParser::findEncrypted(std::string &line) {
    if (!foundEncrypted && line.find("Encryption key:") != std::string::npos) {
        boost::algorithm::trim(line);
        // After trim we have something like: Encryption key:on

        auto encriptionStr = line.substr(line.find_first_of(':') + 1);
        // After substr we have "on" or "off

        encrypted = encriptionStr == "on";
        foundEncrypted = true;
    }
}

void IwlistScanParser::findQuality(std::string &line) {
    if (!foundQuality && line.find("Quality=") != std::string::npos) {
        boost::algorithm::trim(line);
        // After trim we have something like: Quality=27/70 Signal level=-83 dBm

        auto pos = line.find_first_of('=');
        auto len = line.find_first_of(' ') - pos;
        auto qualityStr = line.substr(pos + 1, len);
        // After substr we have something like: 27/70

        std::vector<std::string> qualities;
        boost::split(qualities, qualityStr, boost::algorithm::is_any_of("/"));

        int currentQuality = std::stoi(qualities[0]);
        int maxQuality = std::stoi(qualities[1]);

        // We measure quality in only 4 levels
        quality = (int) std::round((((double) currentQuality) / maxQuality) * 4);
        foundQuality = true;
    }
}

void IwlistScanParser::findAuthentication(std::string &line) {
    if (!foundAuthentication && line.find("Authentication Suites") != std::string::npos) {
        boost::algorithm::trim(line);
        // After trim we have something like: Authentication Suites (1) : PSK

        std::vector<std::string> vect;
        boost::split(vect, line, boost::algorithm::is_any_of(":"));

        authentication = vect[1];
        boost::algorithm::trim(authentication);

        foundAuthentication = true;
    }
}

void IwlistScanParser::removeDuplicates(std::vector<Wifi> &wifis) const {
    std::vector<Wifi> filteredWifis;

    for (auto &wifi : wifis) {
        bool isNew = true;
        for (auto &filteredWifi : filteredWifis) {
            if (filteredWifi.ssid == wifi.ssid) {
                isNew = false;
                if (wifi.quality > filteredWifi.quality) {
                    filteredWifi = std::move(wifi);
                }
                break;
            }
        }
        if (isNew) {
            filteredWifis.emplace_back(std::move(wifi)); // NOLINT
        }
    }

    wifis = filteredWifis;
}
