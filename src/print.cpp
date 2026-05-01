#include "print.hpp"
#include "util/camera.hpp"
#include "util/data.hpp"
#include "util/render.hpp"

int runPrint() {
    AppData data;

    int success = singleFrameCapture(data);
    if (success != 0)
        return 1;

    // obtain size information
    updateTerminalSize(data);
    computeImageSize(data);

    // print terminal to screen
    printColor(data);

    return 0;
}
