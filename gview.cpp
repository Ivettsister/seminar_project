#include "gview.hpp"

const int s_width = 1600;
const int s_height = 800;
const int s_size = 8;

Gview::Gview() : window(sf::VideoMode(s_width, s_height), "Snake!")
{
    window.setFramerateLimit(3);
    max_coord.first = s_width / s_size;
    max_coord.second = s_height / s_size;
    /*
    shape_rabbits.setFillColor(sf::Color::Blue);
    shape_python.setFillColor(sf::Color::Red);*/
}

Gview::~Gview() {
    
}

void Gview::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                key_func('w');
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                key_func('a');
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                key_func('s');
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
                key_func('d');
        }


        window.clear();
        update_func();
        window.display();
    }
}


void Gview::draw() {

}

void Gview::draw(const coord& rabbit) {
    sf::CircleShape shape(s_size / 2);
    shape.setPosition(rabbit.first * s_size, rabbit.second * s_size);
    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}

void Gview::draw(const coords& body, dir dir) {
    sf::RectangleShape shape(sf::Vector2f(4, 4));
    for (auto segment : body) {
        shape.setPosition(segment.first * s_size, segment.second * s_size);
        shape.setFillColor(sf::Color::Green);
        window.draw(shape);
    }
}
