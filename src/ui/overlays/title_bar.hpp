#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"

using namespace ftxui;

inline Component TitleBar() {
    return Renderer([]() {
        return vbox(
            {hbox({filler(), separatorEmpty(), text("Text sight") | underlined,
                   separatorEmpty(), filler()}),
             filler()});
    });
}
