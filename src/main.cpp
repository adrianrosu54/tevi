#include <iostream>
#include <string>

#include "args.hpp"
#include "print.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return runPrint();
    }

    std::string command{argv[1]};

    if (command == "print") {
        return runPrint(parseArgs(argc, argv));
    } else {
        std::cerr << "Error: Unknown command\n";
        return 1;
    }

    return 0;
}
