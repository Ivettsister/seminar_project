#pragma once

#include <iostream>
#include <functional>
#include "game.hpp"

class Control {
    private:
    Game* game;

    public:
    Control(Game* g);
};

class Human {
    public:
    Human();
    void key_pressed(int code);
};