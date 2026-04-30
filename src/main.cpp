#include <asm-generic/ioctls.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "data.hpp"
#include "render.hpp"

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: could not open camera\n";
        return 1;
    }

    AppData data;

    // obtain size information
    updateCameraSize(data, cap);
    updateTerminalSize(data);
    computeImageSize(data);

    // read from camera
    bool ret = cap.read(data.frame);

    if (!ret) {
        std::cerr << "Error: Could not read camera frame\n";

        cap.release();
        return 1;
    }

    // print terminal to screen
    printColor(data);

    cap.release();
    return 0;
}
