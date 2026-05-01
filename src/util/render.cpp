#include <cstdint>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <string>

#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

#include "util/data.hpp"
#include "util/render.hpp"

void paintColorBlock(std::string &buffer, const cv::Mat &frame, int row,
                     int col) {
    // sample pixels
    const cv::Vec3b top = frame.at<cv::Vec3b>(2 * row, col);
    const cv::Vec3b bot = frame.at<cv::Vec3b>(2 * row + 1, col);
    // foreground + background
    buffer += "\033[38;2;";
    buffer += std::to_string(top[2]) + ";" + std::to_string(top[1]) + ";" +
              std::to_string(top[0]) + ";";
    buffer += "48;2;";
    buffer += std::to_string(bot[2]) + ";" + std::to_string(bot[1]) + ";" +
              std::to_string(bot[0]) + "m▀";
}

void paintGreyBlock(std::string &buffer, const cv::Mat &frame, int row,
                    int col) {
    const std::uint8_t top = frame.at<std::uint8_t>(2 * row, col);
    const std::uint8_t bot = frame.at<std::uint8_t>(2 * row + 1, col);

    buffer += "\033[38;2;";
    buffer += std::to_string(top) + ";" + std::to_string(top) + ";" +
              std::to_string(top) + ";";
    buffer += "48;2;";
    buffer += std::to_string(bot) + ";" + std::to_string(bot) + ";" +
              std::to_string(bot) + "m▀";
}

void renderBlocks(const AppData &data, bool color) {
    cv::Mat resized;
    // double the height for double unicode block rendering
    cv::Size size(data.projWidth, 2 * data.projHeight);

    cv::resize(data.sourceFrame, resized, size, 0, 0, cv::INTER_AREA);

    // estimate 30 bytes per pixel ANSI sequence
    std::string buffer;
    buffer.reserve(data.projWidth * data.projHeight * 30);

    // render loop
    for (int row{}; row < data.projHeight; ++row) {
        for (int col{}; col < data.projWidth; ++col) {
            if (color)
                paintColorBlock(buffer, resized, row, col);
            else
                paintGreyBlock(buffer, resized, row, col);
        }
        buffer += "\033[0m\n";
    }

    std::cout << buffer << std::flush;
    std::cout << "\033[0m" << std::flush;
}
