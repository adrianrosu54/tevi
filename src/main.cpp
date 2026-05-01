#include <iostream>
#include <stdexcept>
#include <string>

#include "args.hpp"
#include "print.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return runPrint();
    }

    std::string command{argv[1]};

    if (command == "print") {
        try {
            Config config(parseArgs(argc, argv));

            runPrint(config);
        } catch (std::invalid_argument e) {
            std::cerr << "Error: " << e.what() << "\n";
            printHelp();
            return -1;
        }
    } else if (command == "live") {

    } else if (command == "--version") {
        std::cout << "version: " TEVI_VERSION "\n";
    } else if (command == "--help") {
        printHelp();
    } else {
        std::cerr << "Error: Unknown command\n";
        printHelp();
        return 1;
    }

    return 0;
}
