//
// Created by julian on 13.07.18.
//

#ifndef VIEW_IOT_CLIENT_OUTPUTWRITER_H
#define VIEW_IOT_CLIENT_OUTPUTWRITER_H


#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

class OutputWriter {

public:
    void prepareFrame(const cv::Mat& frame, double timeMs, double fps);
    void prepareRow(cv::Mat &frame, const cv::Mat &detectionMat, int row);
    void print(const cv::Mat& frame, int personCount);

};


#endif //VIEW_IOT_CLIENT_OUTPUTWRITER_H
