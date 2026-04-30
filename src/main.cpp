#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: could not open camera\n";
        return 1;
    }

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::cout << "Camera opened: " << width << "x" << height << "\n";

    cap.release();
    return 0;
}
