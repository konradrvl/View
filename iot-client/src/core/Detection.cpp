//
// Created by julian on 09.04.18.
//

#include "Detection.h"

#include <fstream>
#include <iostream>
#include <chrono>

#include <boost/filesystem.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

const int Detection::PROBABILITY_INDEX = 5;
const int Detection::FRAME_GRAB_RATE_MS = 100;

Detection::Detection(const std::string &cfg, const std::string &weights, const std::string &names,
                     float threshold, bool enableVideoOutput)
        : threshold(threshold), enableVideoOutput(enableVideoOutput) {

    if (!boost::filesystem::exists(cfg)) {
        throw std::runtime_error(cfg + " doesn't exist!");
    }

    if (!boost::filesystem::exists(weights)) {
        throw std::runtime_error(weights + " doesn't exist!");
    }

    if (!boost::filesystem::exists(names)) {
        throw std::runtime_error(names + " doesn't exist!");
    }

    net = std::make_unique<cv::dnn::Net>(cv::dnn::readNetFromDarknet(cfg, weights));

    if (net->empty()) {
        throw std::runtime_error("Couldn't create net!");
    }

    readNames(names);
}

bool Detection::isStarted() const {
    return started;
}

void Detection::start(int cameraDevice) {
    if (!started) {
        videoCapture = std::make_unique<cv::VideoCapture>(cameraDevice);

        if (!videoCapture->isOpened()) {
            throw std::runtime_error("Couldn't find camera: " + std::to_string(cameraDevice));
        }

        started = true;

        std::thread([this]() { this->readFrames(); }).detach();
        std::thread([this]() { this->runRecognition(); }).detach();
    }
}

void Detection::stop() {
    if(videoCapture != nullptr) {
        videoCapture->release();
    }

    started = false;
}

void Detection::readFrames() {
    auto lastUpdate = std::chrono::system_clock::now();

    while (started) {
        try {
            cv::Mat currentFrameTemp;
            *videoCapture >> currentFrameTemp;

            auto now = std::chrono::system_clock::now();
            auto diff = now - lastUpdate;

            if (diff.count() > FRAME_GRAB_RATE_MS) {
                std::lock_guard<std::mutex> lock(frameMutex);
                currentFrame = currentFrameTemp;
            }

            lastUpdate = now;
        } catch (const std::exception &exception) {
            stop();
            throw std::runtime_error("Couldn't read frame from camera");
        }
    }
}

void Detection::runRecognition() {
    while (started) {
        try {
            cv::Mat frame;

            {
                std::lock_guard<std::mutex> lock(frameMutex);
                frame = currentFrame;
            }

            detect(frame);
        } catch (const std::exception &exception) {
            stop();
            throw exception;
        }
    }
}

void Detection::detect(cv::Mat &picture) {
    if (!picture.empty()) {
        if (picture.channels() == 4) {
            cvtColor(picture, picture, cv::COLOR_BGRA2BGR);
        }

        auto inputBlob = cv::dnn::blobFromImage(picture, 1 / 255.F, cv::Size(416, 416), cv::Scalar(), true,
                                                false);
        net->setInput(inputBlob, "data");

        auto detectionMat = net->forward("detection_out");

        handleNetResult(picture, detectionMat);
    }
}

void Detection::handleNetResult(cv::Mat &frame, const cv::Mat &detectionMat) {
    std::vector<double> layersTimings;
    double tickFreq = cv::getTickFrequency();
    double timeMs = net->getPerfProfile(layersTimings) / tickFreq * 1000;
    double fps = 1000.f / timeMs;

    if (enableVideoOutput) {
        outputWriter.prepareFrame(frame, timeMs, fps);
    }

    const int probabilitySize = detectionMat.cols - PROBABILITY_INDEX;

    int count = 0;

    for (int i = 0; i < detectionMat.rows; i++) {
        const auto row = detectionMat.row(i);

        const auto fromIt = row.begin<float>() + PROBABILITY_INDEX;
        const auto toIt = fromIt + probabilitySize;

        const auto objectClass = std::max_element(fromIt, toIt).pos().x - PROBABILITY_INDEX;

        float confidence = detectionMat.at<float>(i, objectClass + PROBABILITY_INDEX);

        if (confidence > threshold) {
            const auto &className = classNames[objectClass];
            if (className == "person") {
                count++;

                if (enableVideoOutput) {
                    outputWriter.prepareRow(frame, detectionMat, i);
                }
            }
        }
    }

    if (enableVideoOutput) {
        outputWriter.print(frame, count);
    }

    personCounted(count, timeMs, fps);
}

void Detection::readNames(const std::string &names) {
    std::ifstream classNamesFile(names);

    std::string className;
    while (std::getline(classNamesFile, className)) {
        classNames.push_back(std::move(className));
    }
}
