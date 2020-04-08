//
// Created by julian on 23.05.18.
//

#include "WifiConnector.h"

#include <iostream>

#include "LinuxSystemAccess.h"
#include "HttpServer.h"

#include "../util/Util.h"

const int WifiConnector::CHECK_CONNECTION_INTERVALL = 2000;

WifiConnector::WifiConnector() : config(Util::readConfig()) {
}

void WifiConnector::start() {

    if(!startRequired()) {
        return;
    }

    std::cout << "Will initialize wifi connector" << std::endl;

    bool disableAP = config.find("disableAP") != config.end() && config["disableAP"].get<bool>();

    if(!disableAP && !LinuxSystemAccess::isRoot()) {
        throw std::runtime_error("Application is not running with root rights!");
    }

    if(!disableAP && !LinuxSystemAccess::hasWirelessTools()) {
        throw std::runtime_error("wireless-tools aren't installed!");
    }

    if(!disableAP && !LinuxSystemAccess::hasWifiInterface()) {
        throw std::runtime_error("System has no wifi interface!");
    }

    Util::checkConfig(config, { "httpPort", "httpRoot" });

    const std::string& httpRoot = Util::buildDataFilePath(config["httpRoot"]);
    int httpPort = config["httpPort"];

    if(!disableAP) {
        std::cout << "Starting AP" << std::endl;
        LinuxSystemAccess::initAp();
        LinuxSystemAccess::startAp();
    } else {
        std::cout << "Access Point is disabled by config" << std::endl;
    }

    auto server = std::make_shared<HttpServer>();

    server->connectWifiRequested.connect([this](std::string ssid, std::string passwd) { this->onConnectWifiRequested(std::move(ssid), std::move(passwd)); });

    std::thread([=]() { server->start(httpPort, httpRoot); }).detach();

    std::cout << "Will wait for network connection" << std::endl;

    while(startRequired()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(CHECK_CONNECTION_INTERVALL));
    }

    server->stop();
}

void WifiConnector::onConnectWifiRequested(std::string ssid, std::string passwd) {
    bool connected = LinuxSystemAccess::connectWifi(ssid, passwd);

    if (!connected) {
        std::cout << "Starting AP again" << std::endl;
        LinuxSystemAccess::startAp();
    }
}

bool WifiConnector::startRequired() {
    bool needToStart = true;

    if(config.find("disableWifiConnect") != config.end()) {
        bool disable = config["disableWifiConnect"];
        if(disable) {
            std::cout << "WifiConnect is disabled by config" << std::endl;
            needToStart = false;
        }
    }

    if(LinuxSystemAccess::isConnected()) {
        config["disableWifiConnect"] = true;
        Util::writeConfig(config);
        LinuxSystemAccess::stopAp();
        needToStart = false;
    }

    return needToStart;
}
