#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"

#include "app/app_state.hpp"
#include "ui/image_canvas.hpp"
#include "ui/overlays/command_line.hpp"
#include "ui/overlays/status_window.hpp"
#include "ui/overlays/title_bar.hpp"

#include "ui/view.hpp"

using namespace ftxui;

Component MakeView(AppState &state, Component container,
                   Component commandInput) {
    return Renderer(container, [&]() {
        return dbox({
            ImageCanvas(state)->Render(),
            TitleBar()->Render(),
            StatusWindow(state)->Render(),
            commandLine(state, commandInput)->Render(),
        });
    });
}
