#include "control.hpp"

Control::Control(Game* g) {
    game = g;
}

void Control::get_user_input() {

    char name[20] = {};
    std::cin >> name;
    game->set_name(name);
}