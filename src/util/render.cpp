#include <iostream>
#include <string>

#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

#include "util/data.hpp"
#include "util/render.hpp"

void computeImageSize(AppData &data) {
    // width * 2 to account for terminal character heights
    const float aspectRatio =
        static_cast<float>(data.cameraWidth * 2) / data.cameraHeight;

    int projectionWidth = static_cast<float>(data.termHeight) * aspectRatio;
    int projectionHeight;

    if (projectionWidth > data.termWidth) {
        projectionHeight = static_cast<float>(data.termWidth) / aspectRatio;
        projectionWidth = data.termWidth;
    } else {
        projectionHeight = data.termHeight;
    }

    data.projWidth = projectionWidth;
    data.projHeight = projectionHeight;
}

void printColor(const AppData &data) {
    cv::Mat resized;
    // double the height for double unicode block rendering
    cv::Size size(data.projWidth, 2 * data.projHeight);

    cv::resize(data.frame, resized, size, 0, 0, cv::INTER_LINEAR);

    // estimate 30 bytes per pixel ANSI sequence
    std::string buffer;
    buffer.reserve(data.projWidth * data.projHeight * 30);

    // render loop
    for (int row{}; row < data.projHeight; ++row) {
        for (int col{}; col < data.projWidth; ++col) {
            // sample pixels
            const cv::Vec3b top = resized.at<cv::Vec3b>(2 * row, col);
            const cv::Vec3b bot = resized.at<cv::Vec3b>(2 * row + 1, col);

            // foreground + background
            buffer += "\033[38;2;";
            buffer += std::to_string(top[2]) + ";" + std::to_string(top[1]) +
                      ";" + std::to_string(top[0]) + ";";
            buffer += "48;2;";
            buffer += std::to_string(bot[2]) + ";" + std::to_string(bot[1]) +
                      ";" + std::to_string(bot[0]) + "m▀";
        }
        buffer += "\033[0m\n";
    }

    std::cout << buffer << std::flush;
    std::cout << "\033[0m" << std::flush;
}
