if (WITH_WIFI_CONNECTOR)
    add_executable(view-iot-client-wifi-connector-test IwlistScanParserTest.cpp IwlistScanParserTest.h IwListScannData.h)

    target_link_libraries(view-iot-client-wifi-connector-test PUBLIC view-iot-client-wifi-connector GTest::GTest GTest::Main)

    gtest_discover_tests(view-iot-client-wifi-connector-test)
endif()