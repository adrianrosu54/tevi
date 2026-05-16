#include <filesystem>
#include <stdexcept>
#include <string>

#ifndef NDEBUG
#include <ios>
#include <iostream>
#endif // NDEBUG

#include "args.hpp"

namespace fs = std::filesystem;

Config parseArgs(int argc, char **argv) {
    Config config;

    for (int i{2}; i < argc; ++i) {
        std::string arg{argv[i]};

        if ((arg == "-f" || arg == "--file") && i + 1 < argc) {
            std::string fileName = std::string(argv[++i]);
            // validate existence
            if (!fs::exists(fileName))
                throw std::invalid_argument("File \"" + fileName +
                                            "\" doesn't exist");
            // validate extension
            fs::path file(fileName);
            std::string ext = file.extension().string();

            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
                config.sourceType = Source::PHOTO;
            else if (ext == ".mp4" || ext == ".mov")
                config.sourceType = Source::VIDEO;
            else
                throw std::invalid_argument("Invalid file extension \"" + ext +
                                            "\"");

            config.sourcePath = fileName;
        } else if ((arg == "--height" || arg == "-h") && i + 1 < argc) {
            try {
                const int val = std::stoi(argv[++i]);
                if (val > 0)
                    config.height = val;
                else
                    throw std::invalid_argument("invalid height");
            } catch (std::invalid_argument) {
                throw std::invalid_argument("invalid height");
            }
        } else if ((arg == "--width" || arg == "-w") && i + 1 < argc) {
            try {
                const int val = std::stoi(argv[++i]);
                if (val > 0)
                    config.width = val;
                else
                    throw std::invalid_argument("invalid width");
            } catch (std::invalid_argument) {
                throw std::invalid_argument("invalid width");
            }
        } else if (arg == "--ascii") {
            config.ascii = true;
        } else if (arg == "--grey" || arg == "--gray") {
            config.grey = true;
        } else {
            throw std::invalid_argument("Unknown argument \"" + arg + "\"");
        }
    }

#ifndef NDEBUG
    std::cerr << "---ArgsConfig---\n";
    std::cerr << "fileName \t= " << config.sourcePath << "\n";
    std::cerr << "height \t= " << config.height << "\n";
    std::cerr << "width \t= " << config.width << "\n";
    std::cerr << "grey \t= " << std::boolalpha << config.grey << "\n";
    std::cerr << "ascii \t= " << std::boolalpha << config.ascii << "\n";
    std::cerr << "----------------\n";
#endif // NDEBUG

    return config;
}
