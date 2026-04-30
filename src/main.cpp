#include "app/app_controller.hpp"
#include "app/app_state.hpp"

int main() {
    AppState state{};

    AppController controller(state);
    controller.run();
}
