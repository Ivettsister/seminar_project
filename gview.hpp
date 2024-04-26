#include <SFML/Graphics.hpp>

#include "view.hpp"

class Gview: public View {
    public:
    void draw() override;
    void draw(const coord& rabbit) override;
    void draw(const coords& body, dir dir) override;
    void draw_score(int score) override;
    void draw_frame();
    virtual void run() override;
    void quit_game();
    Gview();
    ~Gview();

    private:
    void process_events();
    void display();

    sf::Sprite rabbit;
    sf::Texture rabbit_texture;

    sf::Sprite snake_body;
    sf::Texture snake_body_texture;

    sf::Sprite snake_head;
    sf::Texture snake_head_texture;

    sf::Text text_box;
    sf::Font font;

    sf::RenderWindow window;
    sf::CircleShape shape_rabbits;
    sf::RectangleShape shape_python;
};