#pragma once

#include <functional>
#include <string>

#include <opencv2/core/mat.hpp>

using PixelPainter = std::function<void(
    std::string &buffer, const cv::Mat &frame, int row, int col)>;

void paintColorBlock(std::string &buffer, const cv::Mat &frame, int row,
                     int col);

void paintGreyBlock(std::string &buffer, const cv::Mat &frame, int row,
                    int col);

void paintColorAscii(std::string &buffer, const cv::Mat &frame, int row,
                     int col);

void paintAscii(std::string &buffer, const cv::Mat &frame, int row, int col);
