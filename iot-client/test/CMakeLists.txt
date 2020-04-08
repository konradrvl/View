find_package(GTest)

if(${GTEST_FOUND})
    option(WITH_TESTS ON)
    if(WITH_TESTS)
        enable_testing()

        add_subdirectory(wifiConnector)
        add_subdirectory(core)
    endif()
endif(${GTEST_FOUND})
