//
// Created by julian on 16.04.18.
//

#ifndef VIEW_IOTCLIENT_IOTCLIENT_H
#define VIEW_IOTCLIENT_IOTCLIENT_H

#include <json.hpp>

#include "Detection.h"
#include "WebsocketConnection.h"

class IotClient {

public:
    IotClient();

    void start();

private:
    nlohmann::json config;

    std::unique_ptr<Detection> detection;
    std::unique_ptr<WebsocketConnection> connection;

    int currentPersonCount = -1;

    void websocketConnected();
    void websocketDisconnected();

    void personCountChanged(int count, double timeMs, double fps);

    void createDetection();
    void createConnection();

};


#endif //VIEW_IOTCLIENT_IOTCLIENT_H
