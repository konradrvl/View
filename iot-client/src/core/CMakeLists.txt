if(NOT EXISTS ${PROJECT_SOURCE_DIR}/data/)
    message(FATAL_ERROR "data dir is missing")
endif()

if(MINGW)
    # Need 3.4.2 because of https://github.com/opencv/opencv/pull/10936
    find_package(OpenCV 3.4.2 REQUIRED)
else()
    find_package(OpenCV 3.3.1 REQUIRED)
endif()

# add target

add_library(view-iot-client-core Detection.cpp Detection.h WebsocketConnection.cpp WebsocketConnection.h IotClient.cpp IotClient.h MessageType.h OutputWriter.cpp OutputWriter.h)

target_compile_definitions(view-iot-client-core PUBLIC _WEBSOCKETPP_CPP11_STL_)

target_link_libraries(view-iot-client-core PUBLIC view-iot-client-util Threads::Threads Boost::boost ${OpenCV_LIBRARIES})

target_include_directories(view-iot-client-core PUBLIC ${OpenCV_INCLUDE_DIRS} 
                                                       ${PROJECT_SOURCE_DIR}/lib/json
                                                       ${PROJECT_SOURCE_DIR}/lib/websocketpp)

# Copy

file(COPY ${PROJECT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/${DATA_DIR}/data)

# install

install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/ DESTINATION ${DATA_DIR}/data)
