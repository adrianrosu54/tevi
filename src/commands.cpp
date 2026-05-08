#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <thread>

#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include "args.hpp"
#include "render.hpp"
#include "util/data.hpp"
#include "util/fetcher.hpp"
#include "util/pixel.hpp"

#include "commands.hpp"

void restoreTerminal() {
    std::cout << "\033[?7h"    // re-enable line wrap
                 "\033[?25h"   // show cursor
                 "\033[0m"     // reset colors
                 "\033[?1049l" // alternate buffer
              << std::flush;
}

void handleSignal(int) {
    restoreTerminal();
    std::exit(0);
}

void runPrint(const Config &config) {
    AppData data;

    // obtain painter settings
    PixelPainter painter;
    if (config.ascii)
        painter = (config.grey) ? paintAscii : paintColorAscii;
    else
        painter = (config.grey) ? paintGreyBlock : paintColorBlock;

    // extract image from source
    SourceFetcher fetch = setSourceFetcher(config, data);
    data.sourceFrame = fetch();

    // obtain size information
    updateTerminalSize(data);
    data.termHeight -= 1; // account for prompt line in CLI

    updateProjectionSize(config, data);

    // account for double height on block drawings
    data.processingHeight =
        (config.ascii) ? data.projHeight : 2 * data.projHeight;

#ifndef NDEBUG
    std::cerr << "---DIMENSIONS---\n";
    std::cerr << "Source size: \t" << data.sourceWidth << "x"
              << data.sourceHeight << "\n";
    std::cerr << "Terminal size: \t" << data.termWidth << "x" << data.termHeight
              << "\n";
    std::cerr << "Projection size: \t" << data.projWidth << "x"
              << data.projHeight << "\n";
    std::cerr << "----------------\n";
#endif // NDEBUG

    // render to screen
    renderImage(data, painter);
}

void runStream(const Config &config) {
    AppData data;

    PixelPainter painter;
    if (config.ascii)
        painter = (config.grey) ? paintAscii : paintColorAscii;
    else
        painter = (config.grey) ? paintGreyBlock : paintColorBlock;

    data.processingHeight =
        (config.ascii) ? data.projHeight : 2 * data.projHeight;

    // get source
    SourceFetcher fetch = setSourceFetcher(config, data);

    // setup terminal
    std::cout << "\033[?1049h" // alternate buffer
                 "\033[?25l"   // hide cursor
                 "\033[?7l"    // disable line wrap
                 "\033[2J"     // clear screen
              << std::flush;

    std::atexit(restoreTerminal);
    std::signal(SIGINT, handleSignal);

    bool running = true;
    while (running) {
        data.sourceFrame = fetch();

        updateTerminalSize(data);
        data.termHeight -= 1; // account for prompt line in CLI

        updateProjectionSize(config, data);

        data.processingHeight =
            (config.ascii) ? data.projHeight : 2 * data.projHeight;

        std::cout << "\033[H";
        renderImage(data, painter);

        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}
