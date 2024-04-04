#include <iostream>
#include <random>
#include <list>

#include "game.hpp"
#include "view.hpp"

coord Game::get_rand_coord(){
    coord place = View::get() -> get_max_coord();

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

Snake* Game::get_snake() {
    auto v = View::get();
    coord start = {v -> get_max_coord().first / 3, v -> get_max_coord().second / 3};
    snakes.push_back(Snake(start));

    return &snakes.back();
}

void Game::update(){
    auto v = View::get();

    snake_action();

/////////////////////////////////////

    v->draw();

    for (auto r : rabbits)
        v -> draw(r);
    
    for (auto s : snakes)
        v -> draw(s.body, s.direction);

}

Snake::Snake(coord head) {
    coord cur = head;
    for (int i = 0; i < 5; i++){
        body.push_back(coord (cur));
        cur.second--;
    }
}

void Game::snake_action() {
    for (auto& snake : snakes) {
        auto new_head = snake.body.front();
        switch (snake.direction) {
            case dir::UP: 
                new_head.first--;
                break;

            case dir::DOWN:
                new_head.first++;
                break;

            case dir::RIGHT:
                new_head.second++;
                break;

            case dir::LEFT:
                new_head.second--;
                break;
        }
        bool found = false;
        for (auto rabbit = rabbits.begin(); rabbit != rabbits.end(); ++rabbit) {
            if (((*rabbit).first == new_head.first) && ((*rabbit).second == new_head.second)) { // write operator ==
                auto eaten = rabbit;
                rabbits.erase(eaten);
                found = true;
                break;
            }
        }
        snake.body.push_front(new_head);
        if (!found) snake.body.pop_back();
    }
}