#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "app/app_state.hpp"

#include "services/command_registry.hpp"

static std::vector<std::string> tokenize(const std::string &str) {
    std::istringstream iss(str);

    return {std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}};
}

void CommandRegistry::registerCommand(std::string name, CommandFunction func) {
    m_commands[std::move(name)] = std::move(func);
}

void CommandRegistry::execute(AppState &state, const std::string &input) {
    // obtain command tokens
    auto tokens = tokenize(input);
    if (tokens.empty())
        return;

    // find command in registry
    const auto it = m_commands.find(tokens[0]);
    if (it == m_commands.end())
        throw std::runtime_error("Error: Unknown command");

    // execute
    it->second(state, tokens);
}

void CommandRegistry::init() {
    registerCommand(
        ":q", [](AppState &state, auto &) { state.isLoopRunning = false; });
    registerCommand(
        ":quit", [](AppState &state, auto &) { state.isLoopRunning = false; });
}
