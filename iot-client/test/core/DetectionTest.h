//
// Created by julian on 19.07.18.
//

#ifndef VIEW_IOT_CLIENT_DETECTIONTEST_H
#define VIEW_IOT_CLIENT_DETECTIONTEST_H

#include <gtest/gtest.h>

#include "../../src/core/Detection.h"

class DetectionTest : public ::testing::Test {

protected:
    static const int TIMEOUT_TIME;

    std::unique_ptr<Detection> detection;

    void SetUp() override;

    void processPicture(const std::string &picture, int expected);

};


#endif //VIEW_IOT_CLIENT_DETECTIONTEST_H
