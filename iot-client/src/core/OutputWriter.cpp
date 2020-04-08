//
// Created by julian on 13.07.18.
//

#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv/cv.hpp>
#include "OutputWriter.h"

void OutputWriter::prepareFrame(const cv::Mat& frame, double timeMs, double fps) {
    cv::putText(frame, cv::format("FPS: %.2f ; time: %.2f ms", fps, timeMs),
            cv::Point(20, 20), 0, 0.5, cv::Scalar(0, 0, 255));
}

void OutputWriter::prepareRow(cv::Mat &frame, const cv::Mat &detectionMat, int row) {
    float x_center = detectionMat.at<float>(row, 0) * frame.cols;
    float y_center = detectionMat.at<float>(row, 1) * frame.rows;
    float width = detectionMat.at<float>(row, 2) * frame.cols;
    float height = detectionMat.at<float>(row, 3) * frame.rows;
    cv::Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2));
    cv::Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2));
    cv::Rect object(p1, p2);

    cv::Scalar object_roi_color(0, 255, 0);

    rectangle(frame, object, object_roi_color);
}

void OutputWriter::print(const cv::Mat& frame, int personCount) {
    cv::putText(frame, cv::format("Persons: %d", personCount),
                cv::Point(20, 40), 0, 0.5, cv::Scalar(0, 0, 255));

    cv::imshow("YOLO: Detections", frame);
    cv::waitKey(1);
}
