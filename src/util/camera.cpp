#include "camera.hpp"
#include <iostream>

int singleFrameCapture(AppData &data) {
    cv::VideoCapture cap(0);

    updateCameraSize(data, cap);

    if (!cap.isOpened()) {
        std::cerr << "Error: could not open camera\n";
        return 1;
    }

    // read from camera
    bool ret = cap.read(data.sourceFrame);

    if (!ret) {
        std::cerr << "Error: Could not read camera frame\n";

        cap.release();
        return 1;
    }

    cap.release();
    return 0;
}
