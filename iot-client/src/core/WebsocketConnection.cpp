//
// Created by julian on 16.04.18.
//

#include "WebsocketConnection.h"

#include "MessageType.h"

#include <boost/lexical_cast.hpp>

#include <thread>

#include <json.hpp>

const int WebsocketConnection::RECONNECT_TIMEOUT = 5000;

WebsocketConnection::WebsocketConnection(std::string url, std::string serialNumber, std::function<int()> getCurrentPersonCount)
        : url(std::move(url)), serialNumber(std::move(serialNumber)), getCurrentPersonCount(getCurrentPersonCount) {
    client.set_access_channels(websocketpp::log::alevel::none);
    client.set_error_channels(websocketpp::log::alevel::none);

    client.init_asio();

    client.set_open_handler([&] (const auto& hdl) { this->onConnected(hdl); });
    client.set_close_handler([&] (const auto& hdl) { this->onDisconnected(hdl); });
    client.set_message_handler([&] (const auto& hdl, const auto& msgPtr) { this->onMessage(hdl, msgPtr->get_payload()); });
    client.set_fail_handler([&] (const auto& hdl) { this->onFail(hdl); });
}

bool WebsocketConnection::isConnected() const {
    return !hdl.expired();
}

void WebsocketConnection::connect() {
    websocketpp::lib::error_code ec;
    auto conn = client.get_connection(url, ec);

    client.connect(conn);
    client.run();
}

void WebsocketConnection::login() {
    std::cout << "Send login" << std::endl;

    auto msg = buildLoginJson(serialNumber);
    client.send(hdl, msg, websocketpp::frame::opcode::text);
}

std::string WebsocketConnection::buildLoginJson(const std::string &id) {
    nlohmann::json json = {
            { "type", MessageType::LoginIoTDevice },
            {"parameters", {
                              {"id", id}
                      }
            }
    };

    return json.dump();
}

void WebsocketConnection::sendPersonCountChanged(int count) {
    if(isConnected()) {
        auto msg = buildPersonCountChangedJson(count);
        client.send(hdl, msg, websocketpp::frame::opcode::text);
    }
}

std::string WebsocketConnection::buildPersonCountChangedJson(int personCount) {
    nlohmann::json json = {
            { "type", MessageType::PersonCountChanged },
            {"parameters", {
                           {"personCount", personCount},
                           {"timeStamp", dateStringNow()}
                       }
            }
    };

    return json.dump();
}

std::string WebsocketConnection::dateStringNow() {
    auto now = std::time(nullptr);

    return boost::lexical_cast<std::string>(std::put_time(std::localtime(&now), "%Y-%m-%dT%H:%M:%S"));
}

void WebsocketConnection::onMessage(const websocketpp::connection_hdl &hdl, std::string message) {
    if(message == "REQUEST") {
        sendPersonCountChanged(getCurrentPersonCount());
    }

    if(message == "LOGIN_SUCCESS") {
        logedIn();
    }

    if(message == "LOGIN_INVALID") {
        std::cerr << "Login was invalid" << std::endl;
    }
}

void WebsocketConnection::onConnected(const websocketpp::connection_hdl &hdl) {
    std::cout << "Connected to " << url << std::endl;

    this->hdl = hdl;
    connected();

    login();
}

void WebsocketConnection::onDisconnected(const websocketpp::connection_hdl &hdl) {
    this->hdl.reset();
    disconnected();

    std::cerr << "Lost connection to " << url << std::endl;
    reconnect();
}

void WebsocketConnection::onFail(const websocketpp::connection_hdl &hdl) {
    std::cerr << "Couldn't connect to " << url << std::endl;
    reconnect();
}

void WebsocketConnection::reconnect() {
    std::cerr << "Will try again in " << RECONNECT_TIMEOUT << " ms" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(RECONNECT_TIMEOUT));

    connect();
}
