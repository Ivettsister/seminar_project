#include "game.hpp"
#include "control.hpp"
#include "view.hpp"

int main() {
    std::shared_ptr<View> view = View::get("text");
    Game model;
    view -> run();

    return 0;
}