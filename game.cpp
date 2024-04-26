#include <iostream>
#include <random>
#include <list>

#include "game.hpp"
#include "view.hpp"

static FILE* f;

Game::Game(){
    f = fopen("log.txt", "w");
    auto v = View::get();
    fprintf(f, "size of the window: %d, %d\n", v -> get_max_coord().first, v -> get_max_coord().second);
    v->set_update(std::bind(&Game::update, this));

    for (int i = 0; i < num_rabbits; i++){
        add_rabbit();
    }

    for (auto r : rabbits) {
        fprintf(f, "coords r: %d, %d\n", r.first, r.second);
    }
}

coord Game::get_rand_coord(){
    coord place = View::get() -> get_max_coord();

    fprintf(f, "max_coord: %d, %d\n", place.first, place.second);
    fflush(f);

    std::uniform_int_distribution<int> distrib_y (1, place.first);
    std::uniform_int_distribution<int> distrib_x (1, place.second);

    for (;;) {
        place.first = distrib_y(Game::generator);
        place.second = distrib_x(Game::generator);
    
        bool found = false;
        for (const auto& r : rabbits) {
            if (r == place) {
                found = true;
                break;
            }
        }

        for (const auto& s : snakes) {
            for (const auto& segment : s.body) {
                if (segment == place) {
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            fprintf(f, "new_coord: %d, %d\n", place.first, place.second);
            fflush(f);
            return place;
        }
    }
}

void Game::add_rabbit(){
    rabbits.push_back(get_rand_coord());

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
    
    for (auto s : snakes) {
        v -> draw(s.body, s.direction, s.score);
        v -> draw_score(s.score);
    }
}

Snake::Snake(coord head) {
    coord cur = head;
    for (int i = 0; i < 5; i++){
        body.push_back(cur);
        cur.second--;
    }
}

void Game::snake_action() {
    auto v = View::get();
    for (auto& snake : snakes) {
        auto new_head = snake.body.front();
        //fprintf(f, "snake head: %d, %d\n", new_head.first, new_head.second);
        int count = 0;
        for (auto segment : snake.body) {
            if ((count != 0) && (segment == new_head)) {
                snake.score = -1;
            }
            count++;
        }

        if ((new_head.first == 0) || (new_head.first == v->get_max_coord().first)) {
            snake.score = -1;
        }
        if ((new_head.second == 0) || (new_head.second == v->get_max_coord().second)) {
            snake.score = -1;
        }

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
            if (*rabbit == new_head) { 
                rabbits.erase(rabbit);   // changed
                found = true;
                snake.score += 10;
                break;
            }
        }
        snake.body.push_front(new_head);
        if (!found)
            snake.body.pop_back();
        else 
            add_rabbit();
        /*if(found) {
            fprintf(f, "Coords new_head: %d, %d; snake size = %zd; rabbit size = %zd\n", 
            new_head.first, new_head.second, snake.body.size(), rabbits.size());
            fflush(f);
        }*/
    }
}
