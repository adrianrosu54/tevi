#pragma once

#include <string>

struct Config {
    std::string fileName{""};
    int height{0};
    int width{0};
    bool grey{false};
    bool ascii{false};
};

Config parseArgs(int argc, char **argv);

void printHelp();
