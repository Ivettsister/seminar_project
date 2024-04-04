#include "control.hpp"

Control::Control(Snake* s) {
    auto v = View::get();
    snake = s;
    auto f = std::bind(&Control::key_pressed, this, std::placeholders::_1);
    v->set_on_key(f);
}

void Control::key_pressed(int code) {
    switch (code) {
        case 'w':
            snake->direction = dir::UP;
            break;
        case 's':
            snake->direction = dir::DOWN;
            break;
        case 'a':
            snake->direction = dir::LEFT;
            break;
        case 'd':
            snake->direction = dir::RIGHT;
            break;
    }
}