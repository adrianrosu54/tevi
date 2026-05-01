#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdexcept>

#ifndef NDEBUG
#include <iostream>
#endif // !NDEBUG

#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include "print.hpp"
#include "util/camera.hpp"
#include "util/data.hpp"
#include "util/render.hpp"

int runPrint(const Config &config) {
    AppData data;

    // source extraction
    switch (config.sourceType) {
    case Source::CAMERA:
        if (0 != singleFrameCapture(data))
            return 1;
        if (config.grey)
            cv::cvtColor(data.sourceFrame, data.sourceFrame,
                         cv::COLOR_BGR2GRAY);
        break;
    case Source::PHOTO:
        if (config.grey)
            data.sourceFrame =
                cv::imread(config.sourcePath, cv::IMREAD_GRAYSCALE);
        else
            data.sourceFrame =
                cv::imread(config.sourcePath, cv::IMREAD_COLOR_BGR);
        {
            cv::Size sourceSize = data.sourceFrame.size();
            data.sourceWidth = sourceSize.width;
            data.sourceHeight = sourceSize.height;
        }
        break;
    case Source::VIDEO:
        throw std::invalid_argument("Video file printing not supported");
    }

    // obtain size information
    updateTerminalSize(data);
    data.termHeight -= 1; // account for prompt line in CLI

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

#ifndef NDEBUG
    std::cerr << "---DIMENSIONS---\n";
    std::cerr << "Source size: \t" << data.sourceWidth << "x"
              << data.sourceHeight << "\n";
    std::cerr << "Terminal size: \t" << data.termWidth << "x" << data.termHeight
              << "\n";
    std::cerr << "Projection size: \t" << data.projWidth << "x"
              << data.projHeight << "\n";
    std::cerr << "----------------\n";
#endif // !NDEBUG

    // render to screen
    renderBlocks(data, !config.grey);

    return 0;
}
