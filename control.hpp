#pragma once

#include <iostream>
#include <functional>
#include "game.hpp"

class Control {
    private:
    Snake* snake;

    public:
    Control(Snake* snake);
    void key_pressed(int code);
};