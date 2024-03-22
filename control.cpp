#include "control.hpp"

Control::Control(Game* g) {
    game = g;
}

Human::Human() {
    auto f = std::bind(&Human::key_pressed, this, std::placeholders::_1);
}

void Human::key_pressed(int code) {

}