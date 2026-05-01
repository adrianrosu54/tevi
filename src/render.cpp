#include <iostream>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

#include "render.hpp"
#include "render/pixel.hpp"
#include "util/data.hpp"

void renderImage(const AppData &data, PixelPainter painter) {
    cv::Mat resized;

    cv::Size size(data.projWidth, data.processingHeight);

    cv::resize(data.sourceFrame, resized, size, 0, 0, cv::INTER_AREA);

    // estimate 30 bytes per pixel ANSI sequence
    std::string buffer;
    buffer.reserve(data.projWidth * data.projHeight * 30);

    // render loop
    for (int row{}; row < data.projHeight; ++row) {
        for (int col{}; col < data.projWidth; ++col) {
            painter(buffer, resized, row, col);
        }
        buffer += "\033[0m\n";
    }

    std::cout << buffer << std::flush;
}
