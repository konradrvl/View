//
// Created by julian on 16.05.18.
//

#ifndef VIEW_IOT_CLIENT_WIFI_H
#define VIEW_IOT_CLIENT_WIFI_H

#include <string>
#include <utility>

class Wifi {

public:
    std::string ssid;
    int quality{};
    bool encrypted{};

    Wifi() = default;

    Wifi(std::string ssid, int quality, bool encrypted)  : ssid(std::move(ssid)), quality(quality), encrypted(encrypted) {
    }

};


#endif //VIEW_IOT_CLIENT_WIFI_H
