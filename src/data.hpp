#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/videoio.hpp>

struct AppData {
    cv::Mat frame{};
    // camera dimensions
    int cameraWidth{};
    int cameraHeight{};
    // terminal window dimensions
    int termWidth{};
    int termHeight{};
    // image to project dimensions
    int projWidth{};
    int projHeight{};
};

void updateCameraSize(AppData &data, const cv::VideoCapture &cap);

void updateTerminalSize(AppData &data);
