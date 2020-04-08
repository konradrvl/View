cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project(view-iot-client)

# set boost default linking mode

if(WIN32)
    option(Boost_USE_STATIC_LIBS "Use boost static libs" ON)
else()
    option(Boost_USE_STATIC_LIBS "Use boost static libs" OFF)
endif()

# link libgcc if mingw is used

if(MINGW OR (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm"))
    SET(CMAKE_EXE_LINKER_FLAGS -static)
endif()

# Set Directories

if(WIN32)
    set(BINARY_DIR .)
    set(DATA_DIR .)
    set(LIB_DIR .)
else()
    set(BINARY_DIR bin)
    set(DATA_DIR share/${CMAKE_PROJECT_NAME})
    set(LIB_DIR lib)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BINARY_DIR})

file(RELATIVE_PATH DATA_DIR_RELATIVE_TMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR})

if("${DATA_DIR_RELATIVE_TMP}" STREQUAL "")
    set(DATA_DIR_RELATIVE ${DATA_DIR})
else()
    set(DATA_DIR_RELATIVE ${DATA_DIR_RELATIVE_TMP}/${DATA_DIR})
endif()

# Find Libraries

find_package(Boost 1.61 COMPONENTS system filesystem REQUIRED)
find_package(Threads REQUIRED)

# Targets

add_subdirectory(src/util)
add_subdirectory(src/wifiConnector)
add_subdirectory(src/core)
add_subdirectory(src/main)

add_subdirectory(test)

# Copy config file

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(DEBUG_CONFIG_PARAMS "\
,
  \"disableAP\": true,
  \"enableVideoOutput\": true")
endif()

if (WITH_WIFI_CONNECTOR)
    SET(WIFI_CONNECTOR_CONFIG_PARAMS "\
,
  \"disableWifiConnect\": false,
  \"httpPort\": 8080,
  \"httpRoot\": \"web\"")
endif()

configure_file(configuration.json ${CMAKE_BINARY_DIR}/${DATA_DIR}/configuration.json)

# install config file

install(FILES ${CMAKE_BINARY_DIR}/${DATA_DIR}/configuration.json DESTINATION ${DATA_DIR})

if(UNIX)
    install(FILES ${PROJECT_SOURCE_DIR}/service/view-iot-client.service DESTINATION /usr/lib/systemd/system/)
endif()

# CPack

set(CPACK_PACKAGE_CONTACT "The project View")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")

if (WITH_WIFI_CONNECTOR)
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "dnsmasq, hostapd, iptables, isc-dhcp-client, wireless-tools, wpasupplicant")
endif()

include(CPack)
