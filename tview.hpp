#include "view.hpp"
#include "game.hpp"
#include <functional>

class Tview: public View {
    private:
    void hline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem);
    void vline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem);
    void screen_clear();
    void draw(coord& rabbit);
    void draw(coords& body, dir dir);
    struct termios old_state;

    public:
    bool status = true;
    virtual void draw() override;
    virtual void run() override;
    Tview();
    ~Tview();
};