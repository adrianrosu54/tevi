#pragma once

#include <filesystem>

namespace fs = std::filesystem;

enum class Source {
    CAMERA,
    PHOTO,
    VIDEO,
};

struct Config {
    fs::path sourcePath{};
    Source sourceType{Source::CAMERA};
    int height{0};
    int width{0};
    bool grey{false};
    bool ascii{false};
};

Config parseArgs(int argc, char **argv);

void printHelp();
