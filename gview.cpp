#include "gview.hpp"
#include <chrono>
#include <thread>

const int s_width = 1208;
const int s_height = 808;
const int s_size = 10;

Gview::Gview() : window(sf::VideoMode(s_width, s_height), "Snake!")
{
    std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
    window.setFramerateLimit(3);
    max_coord.first = s_width / s_size;
    max_coord.second = s_height / s_size;
    
    if(!rabbit_texture.loadFromFile("krolik.jpg"))
        std::cout<< "Failed downloading krolik_photo!" << std::endl;
    
    sf::Vector2f size_rabbit = sf::Vector2f(rabbit_texture.getSize().x, rabbit_texture.getSize().y);
    rabbit.setTexture(rabbit_texture);
    rabbit.setScale(static_cast<float>(s_size) / size_rabbit.x, static_cast<float>(s_size) / size_rabbit.y);
    //std::cout << "size: " << rabbit_texture.getSize().x * static_cast<float>(s_size) / size_rabbit.x << std::endl;
    
    if(!snake_body_texture.loadFromFile("snakebody.jpeg"))
        std::cout<< "Failed downloading snakebody_photo!" << std::endl;
    sf::Vector2f size_snake = sf::Vector2f(snake_body_texture.getSize().x, snake_body_texture.getSize().y);
    snake_body.setTexture(snake_body_texture);
    snake_body.setScale(static_cast<float>(s_size) / size_snake.x, static_cast<float>(s_size) / size_snake.y);


    if(!snake_head_texture.loadFromFile("snakehead.png"))
        std::cout<< "Failed downloading snakehead_photo!" << std::endl;
    snake_head.setTexture(snake_head_texture);

    text_box.setCharacterSize(24);
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed downloading text_style!" << std::endl;
    }

}

Gview::~Gview() {
    
}
bool is_exit = false;
void Gview::process_events() {
    while (!is_exit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                is_exit = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                key_func('a');
            }
                
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                key_func('w');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                key_func('d');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                key_func('s');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                is_exit = true;
                break;
            } 
        }
    }
}

void Gview::display() {
    while (!is_exit)
    {
        window.clear();
        update_func();
        draw_frame();
        window.display();
    }
    quit_game();
}

void Gview::run() {
    std::thread events(&Gview::process_events, this);
    std::thread displaying(&Gview::display, this);

    events.join();
    displaying.join();
}


void Gview::draw() {

}

void Gview::draw(const coord& rabbit_) {
    //sf::CircleShape shape(s_size);
    rabbit.setPosition(rabbit_.first * s_size, rabbit_.second * s_size);
    //rabbit.setFillColor(sf::Color::Blue);
    window.draw(rabbit);
}

void Gview::draw(const coords& body, dir dir) {
    //sf::RectangleShape shape(sf::Vector2f(s_size, s_size));
    for (auto segment : body) {
        snake_body.setPosition(segment.first * s_size, segment.second * s_size);
        //shape.setFillColor(sf::Color::Green);
        window.draw(snake_body);
    }
}

void Gview::draw_frame() {
    sf::CircleShape square(s_size, 4);
    for (int i = 0; i < s_width; i+=8) {
        square.setPosition(i, 0);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
        square.setPosition(i, s_height - 4);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
    }
    for (int i = 0; i < s_height; i+=8) {
        square.setPosition(0, i);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
        square.setPosition(s_width - 4, i);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
    }
}

void Gview::quit_game() {
    window.clear();
    font.loadFromFile("./arial.ttf");
    text_box.setFont(font);
    text_box.setFillColor(sf::Color::Red);
    text_box.setPosition(s_width / 2 - 100, s_height / 2);
    text_box.setString("Goodbye!");
    window.draw(text_box);
    draw_frame();
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    window.close();
    return;
}
