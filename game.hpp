#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <list>
#include "view.hpp"

class Snake {
    public:

    Snake(coord head);

    coords body;
    dir direction;

    int score;
};

class Game {
    private:
    unsigned short num_rabbits = 5;
    std::list<Snake> snakes;
    std::list<coord> rabbits;
    coord get_rand_coord();
    std::mt19937 generator {static_cast<long unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())};
    void add_rabbit();
    void snake_action();

    public:
    Game();
    void update();
    Snake* get_snake();
};
