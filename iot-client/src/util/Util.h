//
// Created by julian on 24.05.18.
//

#ifndef VIEW_IOT_CLIENT_UTIL_H
#define VIEW_IOT_CLIENT_UTIL_H

#include <string>
#include <vector>

#include <json.hpp>

class Util {

public:
    static std::string buildDataFilePath(const std::string &fileStr);
    static void checkConfig(const nlohmann::json& config, const std::vector<std::string>& attributes);
    static nlohmann::json readConfig();
    static void writeConfig(const nlohmann::json& config);

private:
    static const std::string CONFIGURATION_FILE;

};


#endif //VIEW_IOT_CLIENT_UTIL_H
