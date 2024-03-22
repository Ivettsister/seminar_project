#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <list>
#include "view.hpp"

class Game {
    private:
    unsigned short num_rabbits = 50;
    std::list<coords> snake;
    std::list<coords> rabbits;
    coords get_rand_coord();
    std::mt19937 generator {static_cast<long unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())};
    void add_rabbit();

    public:
    Game();
    void update();
};
