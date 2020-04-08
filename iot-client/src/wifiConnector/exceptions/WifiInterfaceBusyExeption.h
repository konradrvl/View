//
// Created by julian on 24.05.18.
//

#ifndef VIEW_IOT_CLIENT_WIFIINTERFACEBUSYEXEPTION_H
#define VIEW_IOT_CLIENT_WIFIINTERFACEBUSYEXEPTION_H

#include <stdexcept>

class WifiInterfaceBusyExeption : public std::runtime_error {

public:
    WifiInterfaceBusyExeption() : runtime_error("Wifi Interface is busy") {}

    explicit WifiInterfaceBusyExeption(const std::string& msg) : runtime_error(msg) {}

};

#endif //VIEW_IOT_CLIENT_WIFIINTERFACEBUSYEXEPTION_H
