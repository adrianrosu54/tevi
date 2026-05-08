#pragma once

#include <string>

enum class Source {
    CAMERA,
    PHOTO,
    VIDEO,
};

struct Config {
    std::string sourcePath{};
    Source sourceType{Source::CAMERA};
    int height{0};
    int width{0};
    bool grey{false};
    bool ascii{false};
};

Config parseArgs(int argc, char **argv);

void printHelp();
