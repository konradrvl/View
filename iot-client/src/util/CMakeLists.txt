add_library(view-iot-client-util Util.cpp Util.h)

target_link_libraries(view-iot-client-util PRIVATE Boost::filesystem Boost::system ${CMAKE_DL_LIBS})

target_compile_definitions(view-iot-client-util PUBLIC DATA_DIR_RELATIVE="${DATA_DIR_RELATIVE}" BOOST_ALL_NO_LIB)

target_include_directories(view-iot-client-util PUBLIC ${PROJECT_SOURCE_DIR}/lib/json)