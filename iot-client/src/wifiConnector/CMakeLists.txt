include(CMakeDependentOption)

CMAKE_DEPENDENT_OPTION(WITH_WIFI_CONNECTOR "Adds the wifi connector to executable. Only supported under linux" ON "UNIX" OFF)

if (WITH_WIFI_CONNECTOR)

    if (NOT UNIX)
        message(FATAL_ERROR "WITH_WIFI_CONNECTOR is only supported under linux")
    endif ()

    if (NOT EXISTS ${PROJECT_SOURCE_DIR}/web)
        message(FATAL_ERROR "web dir is missing")
    endif ()

    add_library(view-iot-client-wifi-connector LinuxSystemAccess.cpp LinuxSystemAccess.h HttpServer.cpp HttpServer.h Wifi.h wifiJsonConverter.h WifiConnector.cpp WifiConnector.h IwlistScanParser.cpp IwlistScanParser.h)

    target_link_libraries(view-iot-client-wifi-connector PRIVATE Boost::boost
            PUBLIC view-iot-client-util)

    target_include_directories(view-iot-client-wifi-connector PUBLIC ${PROJECT_SOURCE_DIR}/lib/json
            ${PROJECT_SOURCE_DIR}/lib/cpp-httplib
            ${PROJECT_SOURCE_DIR}/lib/pstreams-1.0.1)

    if (WIFI_CONNECTOR_TESTING)
        target_compile_definitions(view-iot-client-wifi-connector PRIVATE WIFI_CONNECTOR_TESTING)
    endif (WIFI_CONNECTOR_TESTING)

    file(COPY ${PROJECT_SOURCE_DIR}/web/ DESTINATION ${CMAKE_BINARY_DIR}/${DATA_DIR}/web)
    file(COPY ${PROJECT_SOURCE_DIR}/scripts/ DESTINATION ${CMAKE_BINARY_DIR}/${DATA_DIR}/scripts)

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/web/ DESTINATION ${DATA_DIR}/web)

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/scripts/ DESTINATION ${DATA_DIR}/scripts
            PATTERN "*.sh" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                                       GROUP_READ GROUP_EXECUTE
                                       WORLD_READ WORLD_EXECUTE)

endif ()