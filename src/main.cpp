#include <iostream>
#include <string>

#include "args.hpp"
#include "print.hpp"
#include "util/logging.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return logAndHandleErrors([]() { runPrint(); });
    }

    std::string command{argv[1]};

    if (command == "print") {
        return logAndHandleErrors([&]() {
            Config config(parseArgs(argc, argv));
            runPrint(config);
        });
    } else if (command == "live") {
        return logAndHandleErrors([&]() {
            Config config(parseArgs(argc, argv));
            runLive(config);
        });
    } else if (command == "--version") {
        std::cout << "version: " TEVI_VERSION "\n";
    } else if (command == "--help") {
        printHelp();
    } else {
        printHelp();
        std::cerr << "Error: Unknown command\n";
        return 1;
    }

    return 0;
}
