#ifndef NDEBUG
#include <iostream>
#endif // !NDEBUG

#include "print.hpp"
#include "util/camera.hpp"
#include "util/data.hpp"
#include "util/render.hpp"

int runPrint(const Config &config) {
    AppData data;

    // source extraction
    int success = singleFrameCapture(data);
    if (success != 0)
        return 1;

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

    // print terminal to screen
    printColor(data);

    return 0;
}
