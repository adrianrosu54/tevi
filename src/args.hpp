#pragma once

#include <string>

enum class Color : char {
    NONE = '_',
    RED = 'r',
    GREEN = 'g',
    BLUE = 'b',
};

struct Config {
    std::string fileName{""};
    int height{0};
    int width{0};
    Color color{Color::NONE};
    Color bgcolor{Color::NONE};
    bool ascii{false};
    bool bold{false};
};

Config parseArgs(int argc, char **argv);
