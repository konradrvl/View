//
// Created by julian on 09.04.18.
//

#ifndef VIEW_IOTCLIENT_DETECTION_H
#define VIEW_IOTCLIENT_DETECTION_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include <boost/signals2.hpp>

#include <opencv2/dnn.hpp>
#include "OutputWriter.h"

class Detection {

public:
    boost::signals2::signal<void(int, double, double)> personCounted;

    Detection(const std::string& cfg, const std::string& weights, const std::string& names, float threshold, bool enableVideoOutput = false);

    bool isStarted() const;

    void start(int cameraDevice);
    void stop();

    void detect(cv::Mat& picture);

private:
    static const int PROBABILITY_INDEX;
    static const int FRAME_GRAB_RATE_MS;

    OutputWriter outputWriter;

    std::unique_ptr<cv::VideoCapture> videoCapture;

    bool started = false;

    std::unique_ptr<cv::dnn::Net> net;

    std::vector<std::string> classNames;

    float threshold;

    bool enableVideoOutput;

    std::mutex frameMutex;

    cv::Mat currentFrame;

    void readFrames();
    void runRecognition();

    void handleNetResult(cv::Mat& frame, const cv::Mat& detectionMat);

    void readNames(const std::string& names);
};

#endif //VIEW_IOTCLIENT_DETECTION_H
