#include "gview.hpp"
#include <chrono>
#include <thread>

const int s_width = 815;
const int s_height = 610;
const int s_size = 20;

Gview::Gview() : window(sf::VideoMode(s_width + 200, s_height), "Snake!")
{
    std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
    window.setFramerateLimit(fps);
    max_coord.first = s_width / s_size;
    max_coord.second = s_height / s_size;
    
    if(!rabbit_texture.loadFromFile("krolik.jpg"))
        std::cout<< "Failed downloading krolik_photo!" << std::endl;
    
    sf::Vector2f size_rabbit = sf::Vector2f(rabbit_texture.getSize().x, rabbit_texture.getSize().y);
    rabbit.setTexture(rabbit_texture);
    rabbit.setScale(static_cast<float>(s_size) / size_rabbit.x, static_cast<float>(s_size) / size_rabbit.y);
    //std::cout << "size: " << rabbit_texture.getSize().x * static_cast<float>(s_size) / size_rabbit.x << std::endl;
    
    if(!snake_body_texture.loadFromFile("snake.jpg"))
        std::cout<< "Failed downloading snakebody_photo!" << std::endl;
    sf::Vector2f size_snake = sf::Vector2f(snake_body_texture.getSize().x, snake_body_texture.getSize().y);
    snake_body.setTexture(snake_body_texture);
    snake_body.setScale(static_cast<float>(s_size) / size_snake.x, static_cast<float>(s_size) / size_snake.y);


    if(!snake_head_texture.loadFromFile("snakehead.jpg"))
        std::cout<< "Failed downloading snakehead_photo!" << std::endl;
    sf::Vector2f size_head = sf::Vector2f(snake_head_texture.getSize().x, snake_head_texture.getSize().y);
    snake_head.setTexture(snake_head_texture);
    snake_head.setScale(static_cast<float>(s_size) / size_head.x, static_cast<float>(s_size) / size_head.y);


    if (!font.loadFromFile("./arial.ttf"))
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

void Gview::draw(const coords& body, dir dir, int score) {
    //sf::RectangleShape shape(sf::Vector2f(s_size, s_size));
    if (score >= 0) {
        int count_segment = 0;
        for (auto segment : body) {
            if (count_segment == 0) {
                snake_head.setPosition(segment.first * s_size, segment.second * s_size);
                window.draw(snake_head);
            }
            else {
                snake_body.setPosition(segment.first * s_size, segment.second * s_size);
                window.draw(snake_body);
            }
            count_segment += 1;
        }
    }
}

void Gview::draw_frame() {
    sf::CircleShape square(s_size / 4, 4);
    for (int i = 0; i < s_width + 200; i+=5) {
        square.setPosition(i, 0);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
        square.setPosition(i, s_height - s_size / 4);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
    }
    for (int i = 0; i < s_height; i+=5) {
        square.setPosition(0, i);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
        square.setPosition(s_width + 200 - s_size / 4, i);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
    }
}

void Gview::draw_score(int score) {
    sf::CircleShape square(s_size / 4, 4);
    for (int i = 0; i < s_height; i+=5) {
        square.setPosition(810, i);
        square.setFillColor(sf::Color::Magenta);
        window.draw(square);
    }
    text_box.setPosition(830, 50);
    text_box.setFont(font);
    text_box.setFillColor(sf::Color::White);
    text_box.setCharacterSize(18);
    text_box.setString("Current rating: " + std::to_string(score));
    window.draw(text_box);
}

void Gview::quit_game() {
    window.clear();
    text_box.setFont(font);
    text_box.setFillColor(sf::Color::Red);
    text_box.setPosition((s_width + 200) / 2 - 100, s_height / 2);
    text_box.setCharacterSize(24);
    text_box.setString("Goodbye!");
    window.draw(text_box);
    draw_frame();
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    window.close();
    return;
}
