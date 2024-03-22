#include <iostream>
#include <random>

#include "game.hpp"
#include "view.hpp"

coords Game::get_rand_coord(){
    coords place = View::get() -> get_max_coord();

    std::uniform_int_distribution<int> distrib_x (2, place.first - 2);
    std::uniform_int_distribution<int> distrib_y (2, place.second - 1);

    place.first = distrib_x(Game::generator);
    place.second = distrib_y(Game::generator);

    return place;
}

void Game::add_rabbit(){
    rabbits.push_back(get_rand_coord());
}

Game::Game(){
    auto v = View::get();
    v->set_update(std::bind(&Game::update, this));

    for (int i = 0; i < num_rabbits; i++){
        add_rabbit();
    }
}

void Game::update(){
    auto v = View::get();

    for (auto r : rabbits)
        v -> draw(r);

}

Snake::Snake(coords head) {
    coords cur = head;
    for (int i = 0; i < 5; i++){
        body.push_back(std::pair<coords, dir>(cur, dir::RIGHT));
        cur.second--;
    }
}

void Game::snake_action() {
    for (auto snake : snakes) {
        // int new_head = snake.body.
    }
}