#include "render/pixel.hpp"
#include <string>

const char *charGradient = " .:-!+|=*xzk#M%@$";

// luminance formula
int luminance(const cv::Vec3b &pixel) {
    return static_cast<int>(0.299 * pixel[2] + 0.587 * pixel[1] +
                            0.114 * pixel[2]);
};

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
    const cv::Vec3b top = frame.at<cv::Vec3b>(2 * row, col);
    const cv::Vec3b bot = frame.at<cv::Vec3b>(2 * row + 1, col);

    const int lt = luminance(top);
    const int lb = luminance(bot);

    buffer += "\033[38;2;" + std::to_string(lt) + ";" + std::to_string(lt) +
              ";" + std::to_string(lt) + ";";
    buffer += "48;2;" + std::to_string(lb) + ";" + std::to_string(lb) + ";" +
              std::to_string(lb) + "m▀";
}

void paintColorAscii(std::string &buffer, const cv::Mat &frame, int row,
                     int col) {
    const cv::Vec3b pixel = frame.at<cv::Vec3b>(row, col);

    const int lum = luminance(pixel);
    const int index = lum * (strlen(charGradient) - 1) / 255;
    const char ch = charGradient[index];

    buffer += "\033[38;2;" + std::to_string(pixel[2]) + ";" +
              std::to_string(pixel[1]) + ";" + std::to_string(pixel[0]) + "m";
    buffer += ch;
}

void paintAscii(std::string &buffer, const cv::Mat &frame, int row, int col) {
    const cv::Vec3b pixel = frame.at<cv::Vec3b>(row, col);

    const int lum = luminance(pixel);
    const int index = lum / 16;
    const char ch = charGradient[index];

    buffer += ch;
}
