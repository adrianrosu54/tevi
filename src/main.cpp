#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#include "args.hpp"
#include "commands.hpp"
#include "util/logging.hpp"

int main(int argc, char *argv[]) {

#ifdef _WIN32
    // Enable UTF-8 encoding on Windows
    SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

    if (argc < 2) {
        return logAndHandleErrors([]() { runStream(); });
    }

    std::string command{argv[1]};

    if (command == "print") {
        return logAndHandleErrors([&]() {
            Config config(parseArgs(argc, argv));
            runPrint(config);
        });
    } else if (command == "stream") {
        return logAndHandleErrors([&]() {
            Config config(parseArgs(argc, argv));
            runStream(config);
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
