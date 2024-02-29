#include "game.hpp"
#include "view.hpp"

void Game::set_name(std::string name) {
    Game::game_name = name;
    view->draw();
}