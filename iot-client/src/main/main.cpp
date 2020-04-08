#ifdef WITH_WIFI_CONNECTOR

#include "../wifiConnector/WifiConnector.h"

#endif

#include "../core/IotClient.h"

int main(int argc, char **argv) {

    try {

#ifdef WITH_WIFI_CONNECTOR
        {
            WifiConnector wifiConnector;
            wifiConnector.start();
        }
#endif

        IotClient client;
        client.start();

    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
        exit(-1);
    }

}
