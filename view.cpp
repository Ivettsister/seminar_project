#include "view.hpp"

View* View::view = NULL;

View* View::get(std::string s) {
        if (view) return view;

        if (s == "text") {
             view = new Tview;
        }
        else {
             view = new Gview;
        }

        return view;
}

void Tview::draw() {
        this->clear_window();
        this->set_colors(20, 33);

        struct winsize wind_sz = {};
        ioctl(0, TIOCGWINSZ, &wind_sz);

        int wind_x_sz = wind_sz.ws_row;
        int wind_y_sz = wind_sz.ws_col;

        for (int i = 1; i < wind_y_sz; i++) {
                gotoxy(1, i);
                puts("=");
                gotoxy(wind_x_sz - 1, i);
                puts("=");
        }

        for (int i = 0; i < wind_x_sz; i++) {
                gotoxy(i, 3);
                puts("||");
                gotoxy(i, wind_y_sz - 1);
                puts("||");
        }

        gotoxy(1, wind_y_sz / 2 - 3);
        puts("SNAKE game!");
}

void Gview::draw() {
}

View::~View() {

}

void Tview::clear_window() {
        std::cout << "\e[H\e[J" << std::flush;

}

void Tview::set_colors(int brightness, int color) {
        std::cout << "\e[" << brightness << ";" << color << "m" << std::flush;
}

void Tview::gotoxy(int x, int y) {
        std::cout << "\e[" << x << ";" << y << "H" << std::flush;
}

void Tview::puts(std::string s) {
        std::cout << s << std::endl;
}