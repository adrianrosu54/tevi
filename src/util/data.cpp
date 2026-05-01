#include <sys/ioctl.h>
#include <unistd.h>

#include "data.hpp"

void updateCameraSize(AppData &data, const cv::VideoCapture &cap) {
    data.sourceWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    data.sourceHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}

void updateTerminalSize(AppData &data) {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    data.termWidth = ws.ws_col;
    data.termHeight = ws.ws_row;
}

void computeImageSize(AppData &data) {
    // width * 2 to account for terminal character heights
    const float aspectRatio =
        static_cast<float>(data.sourceWidth * 2) / data.sourceHeight;

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
