//
// Created by julian on 14.05.18.
//

#include "HttpServer.h"

#include <iostream>

#include <json.hpp>

#include "../util/Util.h"

#include "LinuxSystemAccess.h"
#include "wifiJsonConverter.h"
#include "exceptions/WifiInterfaceBusyExeption.h"

void HttpServer::start(int port, const std::string &httpRoot) {
    server.Get("/api/wifi", [&](const auto &req, auto &res) { this->onRequestedWifiList(req, res); });
    server.Put("/api/wifi", [&](const auto &req, auto &res) { this->onConnectWifi(req, res); });

    server.set_base_dir(httpRoot.c_str());

    server.Get(".*", [&](const auto &req, auto &res) { res.set_redirect("/"); });

    std::cout << "Starting http server on port " << port << std::endl;

    server.listen("0.0.0.0", port);

    std::cout << "Http server stopped" << std::endl;
}

void HttpServer::stop() {
    if (server.is_running()) {
        server.stop();
    }
}

void HttpServer::onRequestedWifiList(const httplib::Request &req, httplib::Response &res) {
    try {
        auto wifiList = LinuxSystemAccess::getWifiList();
        nlohmann::json wifiListJson(wifiList);

        res.set_content(wifiListJson.dump(), "application/json");
    } catch (const WifiInterfaceBusyExeption&) {
        res.status = 500;
        res.set_content("wifiInterfaceBusy", "text/plain");
    }
}

void HttpServer::onConnectWifi(const httplib::Request &req, httplib::Response &res) {
    std::string ssid;
    std::string passwd;

    std::cout << "Connect requested" << std::endl;

    bool success = parseConnectParams(req.body, ssid, passwd);

    if(success) {
        connectWifiRequested(ssid, passwd);
    } else {
        std::cout << "Got illegal connect parameters requested" << std::endl;
        res.status = 500;
        res.set_content("invalidParameter", "text/plain");
    }
}

bool HttpServer::parseConnectParams(const std::string &body, std::string &ssid, std::string &passwd) {
    auto json = nlohmann::json::parse(body);

    bool foundSsid = false;

    if(json.find("params") != json.end()) {
        const auto& jsonParams = json["params"];
        if(jsonParams.find("updates") != jsonParams.end()) {
            const auto& jsonUpdates = jsonParams["updates"];
            if(jsonUpdates.is_array()) {
                for(const auto& param : jsonUpdates) {
                    if(param.find("param") != param.end() && param.find("value") != param.end()) {
                        if(param["param"] == "ssid") {
                            ssid = param["value"];
                            foundSsid = true;
                        }
                        if(param["param"] == "passwd") {
                            passwd = param["value"];
                        }
                    }
                }
            }
        }
    }

    return foundSsid;
}