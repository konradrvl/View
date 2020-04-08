//
// Created by julian on 16.04.18.
//

#include "IotClient.h"
#include "../util/Util.h"

#include <fstream>
#include <boost/format.hpp>

IotClient::IotClient() : config(Util::readConfig()) {
    createConnection();
    connection->logedIn.connect([&]() { websocketConnected(); });
    connection->disconnected.connect([&]() { websocketDisconnected(); });

    createDetection();
    detection->personCounted.connect([&] (int count, double timeMs, double fps) { personCountChanged(count, timeMs, fps); });
}

void IotClient::start() {
    connection->connect();
}

void IotClient::createDetection() {
    Util::checkConfig(config, { "cfg", "weights", "names", "threshold", "cameraDevice" });

    const std::string& cfg = Util::buildDataFilePath(config["cfg"]);
    const std::string& weights = Util::buildDataFilePath(config["weights"]);
    const std::string& namesFile = Util::buildDataFilePath(config["names"]);

    float threshold = config["threshold"];

    bool enableVideoOutput = (config.find("enableVideoOutput") != config.end() && config["enableVideoOutput"].get<bool>());

    detection = std::make_unique<Detection>(cfg, weights, namesFile, threshold, enableVideoOutput);
}

void IotClient::createConnection() {
    Util::checkConfig(config, {"url", "serialNumber"});

    const std::string& url = config["url"];
    const std::string& serialNumber = config["serialNumber"];

    connection = std::make_unique<WebsocketConnection>(url, serialNumber, [&]() { return currentPersonCount; });
}

void IotClient::websocketConnected() {
    int cameraDevice = config["cameraDevice"];

    detection->start(cameraDevice);
}

void IotClient::websocketDisconnected() {
    detection->stop();
    currentPersonCount = -1;
}

void IotClient::personCountChanged(int count, double timeMs, double fps) {
    if(currentPersonCount != count) {
        auto str = (boost::format("Count changed: %d (Detection took %.2f ms with %.2f fps)") % count % timeMs % fps).str();
        std::cout << str << std::endl;
        currentPersonCount = count;
        connection->sendPersonCountChanged(count);
    }

}
