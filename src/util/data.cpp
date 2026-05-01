#include <sys/ioctl.h>
#include <unistd.h>

#include "data.hpp"

void updateCameraSize(AppData &data, const cv::VideoCapture &cap) {
    data.cameraWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    data.cameraHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}

void updateTerminalSize(AppData &data) {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    data.termWidth = ws.ws_col;
    data.termHeight = ws.ws_row;
}
