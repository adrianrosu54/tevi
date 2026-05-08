#include <iostream>

#include "util/logging.hpp"

void printHelp() {
    std::cout << R"(
Usage: tevi [command] [options]

Commands:
    print                   Print image to terminal
    stream                  Stream Output in TUI mode

Options:
    -f, --file <file>       Render from an image file. Supports .png and .jpeg
    -w, --width <cols>      Output width in characters
    -h, --height <rows>     Output height in characters
        --ascii             Print as ascii text
        --grey              Display as greyscale

        --help              Show this message and exit
        --version           Display project version

)";
}

int logAndHandleErrors(std::function<void()> func) {
    try {
        func();
    } catch (std::invalid_argument e) {
        printHelp();
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch (std::runtime_error e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
