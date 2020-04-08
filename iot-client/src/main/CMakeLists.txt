add_executable(view-iot-client main.cpp)
target_link_libraries(view-iot-client PRIVATE view-iot-client-core)

if(WITH_WIFI_CONNECTOR)
    target_compile_definitions(view-iot-client PRIVATE WITH_WIFI_CONNECTOR)
    target_link_libraries(view-iot-client PRIVATE view-iot-client-wifi-connector)
endif(WITH_WIFI_CONNECTOR)

# install

install(TARGETS view-iot-client RUNTIME DESTINATION ${BINARY_DIR})
