#pragma once

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "app/app_state.hpp"
#include "services/command_registry.hpp"

using namespace ftxui;

Component MakeController(AppState &state, CommandRegistry &registry,
                         Component view, Component commandInput,
                         Component focusSink);
