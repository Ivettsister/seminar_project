#include "view.hpp"
#include "game.hpp"
#include <functional>

class Tview: public View {
    private:
    void hline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem);
    void vline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem);
    void screen_clear();
    void gotoxy(const coord& c);
    struct termios old_state;

    public:
    bool status = true;
    virtual void draw() override;
    void draw(const coord& rabbit) override;
    void draw(const coords& body, dir dir, int score) override;
    void draw_score(int score) override;
    virtual void run() override;
    Tview();
    ~Tview();
};