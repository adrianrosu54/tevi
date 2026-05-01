#ifndef NDEBUG
#include <iostream>
#endif // !NDEBUG

#include "print.hpp"
#include "util/camera.hpp"
#include "util/data.hpp"
#include "util/render.hpp"

int runPrint(const Config &config) {
    AppData data;

    int success = singleFrameCapture(data);
    if (success != 0)
        return 1;

    // obtain size information
    updateTerminalSize(data);
    data.termHeight -= 1; // account for prompt line in CLI
    computeImageSize(data);

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
