#include <stdexcept>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"

#include "app/app_state.hpp"
#include "services/command_registry.hpp"

#include "ui/controller.hpp"

using namespace ftxui;

Component MakeController(AppState &state, CommandRegistry &registry,
                         Component view, Component commandInput,
                         Component focusSink) {
    return CatchEvent(view, [&](Event event) {
        // open the command line
        if (event == Event::Character(':') && !state.displayCommand) {
            state.displayCommand = true;
            state.command = ":";
            state.cursorPosition = 1;

            commandInput->TakeFocus();
            return true;
        }
        if (event == Event::Character('q') && !state.displayCommand) {
            state.isLoopRunning = false;
            return true;
        }
        // command line events
        if (event == Event::Escape && state.displayCommand) {
            state.displayCommand = false;
            state.command.clear();

            focusSink->TakeFocus();
            return true;
        }
        if (event == Event::Backspace && state.displayCommand &&
            state.command == ":") {
            state.displayCommand = false;
            state.command.clear();

            focusSink->TakeFocus();
            return true;
        }
        // command execution
        if (event == Event::Return && state.displayCommand) {
            try {
                registry.execute(state, state.command);
            } catch (std::runtime_error e) {
                state.statusMessage = e.what();
                state.displayStatus = true;
            }

            state.command.clear();
            state.displayCommand = false;

            focusSink->TakeFocus();
            return true;
        }
        if (event == Event::Escape && state.displayStatus) {
            state.displayStatus = false;
        }
        return false;
    });
}
