#pragma once

#include "ftxui/component/component_base.hpp"

#include "app/app_state.hpp"

using namespace ftxui;

Component MakeView(AppState &state, Component container,
                   Component commandInput);
