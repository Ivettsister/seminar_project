#include "game.hpp"
#include "control.hpp"
#include "view.hpp"

int main() {
    std::shared_ptr<View> view = View::get("text");
    Game model;
    Control(model.get_snake());
    view -> run();

    return 0;
}