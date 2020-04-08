//
// Created by julian on 19.07.18.
//

#include <opencv2/imgcodecs.hpp>

#include "DetectionTest.h"

#include "../../src/util/Util.h"

#include <future>

const int DetectionTest::TIMEOUT_TIME = 4000;

void DetectionTest::SetUp() {
    auto cfg = Util::buildDataFilePath("data/cfg/yolov2.cfg");
    auto weights = Util::buildDataFilePath("data/yolov2.weights");
    auto names = Util::buildDataFilePath("data/data/coco.names");
    float threshold = 0.2;

    detection = std::make_unique<Detection>(cfg, weights, names, threshold);
}

void DetectionTest::processPicture(const std::string &pictureStr, int expected) {
    bool finished{};

    detection->personCounted.connect([&] (int count, double timeMs, double fps) {
        finished = true;
        ASSERT_EQ(count, expected);
    });

    cv::Mat picture = cv::imread(pictureStr, -1);

    std::async(std::launch::async, [&] () {
        detection->detect(picture);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(TIMEOUT_TIME));

    if(!finished) {
        FAIL();
    }
}

TEST_F(DetectionTest , detectOne) {
    processPicture(Util::buildDataFilePath("test/core/data/1.jpg"), 1);
}

TEST_F(DetectionTest , detectOneSw) {
    processPicture(Util::buildDataFilePath("test/core/data/1sw.jpg"), 1);
}

TEST_F(DetectionTest , detectFour) {
    processPicture(Util::buildDataFilePath("test/core/data/4.webp"), 4);
}

