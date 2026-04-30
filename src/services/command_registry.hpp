#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "app/app_state.hpp"

class CommandRegistry {
  public:
    using Args = std::vector<std::string>;
    using CommandFunction = std::function<void(AppState &, const Args &)>;

    CommandRegistry() { init(); }

    void registerCommand(std::string name, CommandFunction func);

    // execute the given command text
    void execute(AppState &state, const std::string &input);

  private:
    void init();

    std::unordered_map<std::string, CommandFunction> m_commands{};
};
