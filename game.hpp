#pragma once

#include <string.h>
#include "view.hpp"

class Game {
    private:
    View* view;
    std::string game_name;

    public:
    Game(View* view_) : view(view_) {
    }

    void set_name(std::string name);
};