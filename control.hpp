#pragma once

#include <iostream>
#include "game.hpp"

class Control {
    private:
    Game* game;

    public:
    Control(Game* g);
    void get_user_input();
};