#pragma once
// Detector.hpp
#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Detector {
    Mat img;
    vector<Point> centerpoint;
    string objType[3];

public:
    void set_img(Mat& _img); // 设置图像
    void detect(); // 检测函数
    void print();  // 打印结果
};

#endif
