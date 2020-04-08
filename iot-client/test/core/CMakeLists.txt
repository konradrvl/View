add_executable(view-iot-client-core-test DetectionTest.cpp DetectionTest.h)

target_link_libraries(view-iot-client-core-test PUBLIC view-iot-client-core GTest::GTest GTest::Main)

gtest_discover_tests(view-iot-client-core-test)

file(COPY ${PROJECT_SOURCE_DIR}/test/core/data DESTINATION ${CMAKE_BINARY_DIR}/${DATA_DIR}/test/core)