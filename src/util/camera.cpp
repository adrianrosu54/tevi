#include <stdexcept>

#include "camera.hpp"

int singleFrameCapture(AppData &data) {
    cv::VideoCapture cap(0);

    updateCameraSize(data, cap);

    if (!cap.isOpened()) {
        throw std::runtime_error("Could not open camera");
    }

    // read from camera
    bool ret = cap.read(data.sourceFrame);

    if (ret) {
        throw std::runtime_error("Could not read from camera frame");
    }

    cap.release();
    return 0;
}
