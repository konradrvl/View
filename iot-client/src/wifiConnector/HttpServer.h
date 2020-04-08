//
// Created by julian on 14.05.18.
//

#ifndef VIEW_IOT_CLIENT_HTTPSERVER_H
#define VIEW_IOT_CLIENT_HTTPSERVER_H

#include <httplib.h>

#include <boost/signals2/signal.hpp>

class HttpServer
{

  public:
    boost::signals2::signal<void(std::string, std::string)> connectWifiRequested;

    void start(int port, const std::string &httpRoot);
    void stop();

  private:
    httplib::Server server;

    void onRequestedWifiList(const httplib::Request &req, httplib::Response &res);
    void onConnectWifi(const httplib::Request &req, httplib::Response &res);
    bool parseConnectParams(const std::string &body, std::string &ssid, std::string &passwd);
};

#endif //VIEW_IOT_CLIENT_HTTPSERVER_H
