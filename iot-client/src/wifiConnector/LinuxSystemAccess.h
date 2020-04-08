//
// Created by julian on 14.05.18.
//

#ifndef VIEW_IOT_CLIENT_RASPBERRRY_WIFI_ACCESS_H
#define VIEW_IOT_CLIENT_RASPBERRRY_WIFI_ACCESS_H

#include <vector>

#include "Wifi.h"

class LinuxSystemAccess {

public:
    static bool hasWirelessTools();
    static bool isConnected();
    static bool hasWifiInterface();
    static bool isRoot();

    static std::string getWifiInterfaceName();

    static bool connectWifi(const std::string &ssid, const std::string &passwd);

    static void initAp();
    static bool startAp();
    static void stopAp();

    static std::vector<Wifi> getWifiList();

private:
    static std::vector<std::string> executeCmd(const std::string& cmd);

    static void checkIfInterfaceIsBusy(const std::vector<std::string> &vector);

    static void initHostApd();
    static void initDns();
    static void setHostApdConfig();
};


#endif //VIEW_IOT_CLIENT_RASPBERRRY_WIFI_ACCESS_H
