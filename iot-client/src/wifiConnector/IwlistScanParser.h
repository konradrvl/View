//
// Created by julian on 24.05.18.
//

#ifndef VIEW_IOT_CLIENT_IWLISTSCANPARSER_H
#define VIEW_IOT_CLIENT_IWLISTSCANPARSER_H


#include <vector>

#include "Wifi.h"

class IwlistScanParser {

public:
    std::vector<Wifi> parse(std::vector<std::string> &lines);

private:
    bool foundSSid = false;
    bool foundEncrypted = false;
    bool foundQuality = false;
    bool foundAuthentication = false;

    int cell = 1;

    std::string ssid;
    bool encrypted;
    int quality;
    std::string authentication;

    void findCell(const std::string &line, std::vector<Wifi>& wifis);

    void findQuality(std::string &line);

    void findEncrypted(std::string &line);

    void findSsid(std::string &line);

    void findAuthentication(std::string &line);

    void removeDuplicates(std::vector<Wifi> &wifis) const;

};


#endif //VIEW_IOT_CLIENT_IWLISTSCANPARSER_H
