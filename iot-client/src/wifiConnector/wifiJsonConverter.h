//
// Created by julian on 17.05.18.
//

#ifndef VIEW_IOT_CLIENT_WIFIJSONCONVERTER_H
#define VIEW_IOT_CLIENT_WIFIJSONCONVERTER_H

#include <json.hpp>

#include "Wifi.h"

void to_json(nlohmann::json& j, const Wifi& wifi) {
    j["encrypted"] = wifi.encrypted;
    j["quality"] = wifi.quality;
    j["ssid"] = wifi.ssid;
}

void from_json(const nlohmann::json& j, Wifi& wifi) {
    wifi.encrypted = j["encrypted"];
    wifi.quality = j["quality"];
    wifi.ssid = j["ssid"];
}


#endif //VIEW_IOT_CLIENT_WIFIJSONCONVERTER_H
