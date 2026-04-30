#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <opencv2/core.hpp>
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

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: could not open camera\n";
        return 1;
    }

    logCameraResolution(cap);
    logTerminalResolution();

    // hide cursor
    std::cout << "\033[?25l";

    for (int i{}; i < 5; ++i) {
        std::cout << i + 1 << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << '\r';
    }

    // show cursor again
    std::cout << "\n\033[?25h";

    cap.release();
    return 0;
}
