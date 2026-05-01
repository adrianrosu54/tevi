#include "args.hpp"
#include <stdexcept>

#ifndef NDEBUG
#include <ios>
#include <iostream>
#endif // NDEBUG

Config parseArgs(int argc, char **argv) {
    Config config;

    for (int i{2}; i < argc; ++i) {
        std::string arg{argv[i]};

        if (arg == "--file" && i + 1 < argc) {
            config.fileName = std::string(argv[++i]);
        } else if (arg == "--height" && i + 1 < argc) {
            try {
                const int val = std::stoi(argv[++i]);
                if (val > 0)
                    config.height = val;
                else
                    throw std::invalid_argument("invalid height");
            } catch (std::invalid_argument) {
                throw std::invalid_argument("invalid height");
            }
        } else if (arg == "--width" && i + 1 < argc) {
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
        }
    }

#ifndef NDEBUG
    std::cerr << "---ArgsConfig---\n";
    std::cerr << "fileName \t= " << config.fileName << '\n';
    std::cerr << "height \t= " << config.height << '\n';
    std::cerr << "width \t= " << config.width << '\n';
    std::cerr << "ascii \t= " << std::boolalpha << config.ascii << '\n';
    std::cerr << "----------------\n";
#endif // NDEBUG

    return config;
}
