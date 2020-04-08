//
// Created by julian on 16.04.18.
//

#ifndef VIEW_IOTCLIENT_WEBSOCKETCONNECTION_H
#define VIEW_IOTCLIENT_WEBSOCKETCONNECTION_H

#include <string>

#include <boost/signals2.hpp>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

class WebsocketConnection {

public:
    boost::signals2::signal<void()> connected;
    boost::signals2::signal<void()> logedIn;
    boost::signals2::signal<void()> disconnected;

    explicit WebsocketConnection(std::string url, std::string serialNumber, std::function<int()> getCurrentPersonCount);

    bool isConnected() const;

    void connect();

    void sendPersonCountChanged(int count);

private:
    static const int RECONNECT_TIMEOUT;

    const std::string url;
    const std::string serialNumber;

    websocketpp::client<websocketpp::config::asio_client> client;
    websocketpp::connection_hdl hdl;

    std::function<int()> getCurrentPersonCount;

    void login();

    void onConnected(const websocketpp::connection_hdl& hdl);
    void onMessage(const websocketpp::connection_hdl& hdl, std::string message);
    void onDisconnected(const websocketpp::connection_hdl& hdl);
    void onFail(const websocketpp::connection_hdl& hdl);

    void reconnect();

    static std::string dateStringNow();

    static std::string buildPersonCountChangedJson(int personCount);
    static std::string buildLoginJson(const std::string& id);

};

#endif //VIEW_IOTCLIENT_WEBSOCKETCONNECTION_H
