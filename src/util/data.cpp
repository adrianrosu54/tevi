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

void updateProjectionSize(const Config &config, AppData &data) {
    if (config.height == 0 && config.width == 0)
        computeImageSize(data);
    else if (config.height != 0 && config.width != 0) {
        data.projWidth = config.width;
        data.projHeight = config.height;
    } else if (config.height != 0) {
        const float aspectRatio =
            static_cast<float>(data.sourceWidth * 2) / data.sourceHeight;
        data.projHeight = config.height;
        data.projWidth = config.height * aspectRatio;
    } else {
        const float aspectRatio =
            static_cast<float>(data.sourceWidth * 2) / data.sourceHeight;
        data.projWidth = config.width;
        data.projHeight = static_cast<float>(config.width) / aspectRatio;
    }
}
