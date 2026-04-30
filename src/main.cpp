#include <asm-generic/ioctls.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

void logCameraResolution(cv::VideoCapture cap) {
    const int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    const int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::cout << "Camera resolution: \t" << width << "x" << height << "\n";
}

void logTerminalResolution() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    std::cout << "Terminal resolution: \t" << ws.ws_col << "x" << ws.ws_row
              << '\n';
}

cv::Size getProjectionSize(int imageWidth, int imageHeight, int termWidth,
                           int termHeight) {
    // width * 2 to account for terminal character heights
    const float aspectRatio = static_cast<float>(imageWidth * 2) / imageHeight;

    int projectionWidth = static_cast<float>(termHeight) * aspectRatio;
    int projectionHeight;

    if (projectionWidth > termWidth) {
        projectionHeight = static_cast<float>(termWidth) / aspectRatio;
        projectionWidth = termWidth;
    } else {
        projectionHeight = termHeight;
    }

    return cv::Size(projectionWidth, projectionHeight);
}

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: could not open camera\n";
        return 1;
    }

    // basic logging
    logCameraResolution(cap);
    logTerminalResolution();

    // get camera image
    cv::Mat frame;
    bool ret = cap.read(frame);

    if (!ret) {
        std::cerr << "Error: Could not read camera frame\n";

        cap.release();
        return 1;
    }

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    const int termWidth = ws.ws_col;
    const int termHeight = ws.ws_row;
    const int imageWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    const int imageHeight =
        static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    const cv::Size projectionSize =
        getProjectionSize(imageWidth, imageHeight, termWidth, termHeight);

    std::cout << "Terminal projection size \t" << projectionSize.width << "x"
              << projectionSize.height << "\n";

    // print terminal buffer placeholder
    std::string charBuffer(projectionSize.width, 'x');

    for (int i{}; i < projectionSize.height; ++i) {
        std::cout << charBuffer << '\n';
    }

    cap.release();
    return 0;
}
