//
// Created by julian on 23.05.18.
//

#ifndef VIEW_IOT_CLIENT_WIFICONNECTOR_H
#define VIEW_IOT_CLIENT_WIFICONNECTOR_H

#include <string>

#include <json.hpp>

class WifiConnector {

public:
    WifiConnector();

    void start();

private:
    static const int CHECK_CONNECTION_INTERVALL;
    
    nlohmann::json config;

    void onConnectWifiRequested(std::string ssid, std::string passwd);

    bool startRequired();
};


#endif //VIEW_IOT_CLIENT_WIFICONNECTOR_H
