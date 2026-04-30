#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"

#include "app/app_state.hpp"

using namespace ftxui;

inline Component commandLine(AppState &state, Component commandInput) {
    return Maybe(Renderer([&]() {
                     return vbox({
                         filler(),
                         hbox({
                             commandInput->Render(),
                             filler(),
                         }),
                     });
                 }),
                 &state.displayCommand);
}
