#include "view.hpp"
#include <functional>

class Tview: public View {
    private:
    void hline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem);
    void vline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem);
    void screen_clear();
    void draw_frame();
    void draw(coords& rabbit);

    public:
    virtual void draw() override;
    virtual void run() override;
    Tview();
    ~Tview();
};