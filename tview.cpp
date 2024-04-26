#include <sys/ioctl.h>
#include <signal.h>
#include <termios.h>
#include <poll.h>
#include "tview.hpp"

void Tview::run() {
    /*while (!status) {
        event = getnext();
        dispatch event;
    }*/

    struct pollfd input = {0, POLLIN, 0};
    status = true;
    while (status) {
    
        update_func();
        
        if (poll(&input, 1, 1000 / fps) == 1){
            char inc_char;
            read(0, &inc_char, 1);
            key_func(inc_char);
            if (inc_char == 'q')
                status = false;
        }
    }
}

Tview::Tview() {
    tcgetattr(0, &old_state);
    struct termios raw = old_state;    // stty sane <ENTER>
    cfmakeraw(&raw);
    //raw.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(0, TCSANOW, &raw);

    struct winsize win_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size); 
    max_coord.first = win_size.ws_row - 2;
    max_coord.second = win_size.ws_col / 2 - 2;
}  

void Tview::draw() {
    coord c;
    struct winsize win_size;fflush(stdout);

    c.first = win_size.ws_row;
    c.second = win_size.ws_col; 

    screen_clear();

    hline(1, 1, c.second, "\e[33m-");
    vline(2, 1, c.first - 1, "\e[33m#");
    vline(2, c.second, c.first - 1, "\e[33m#");
    hline(c.first, 1, c.second, "\e[33m-");

    fflush(stdout);
}

void Tview::gotoxy(const coord& c) {
    std::cout << "\e[" << c.first + 1 << ";" << c.second * 2 + 2 << "H";
}

void Tview::draw(const coord& rabbit){
    gotoxy(rabbit);
    std::cout << "🐇";
    std::cout << std::flush;
}

void Tview::draw_score(int score) {

}

void Tview::draw(const coords& body, dir dir, int score){

    for (auto segment : body) {
        gotoxy(segment);    // goto xy
        if (segment == body.front()) {
                switch (dir) {
                case dir::RIGHT:
                    std::cout << "\e[96m⇛ ";
                    break;
                case dir::UP:
                    std::cout << "\e[96m⤊ ";
                    break;
                case dir::LEFT:
                    std::cout << "\e[96m⇚ ";
                    break;
                case dir::DOWN:
                    std::cout << "\e[96m⤋ ";
                    break;

                }
        }
        else std::cout << "◉ ";
    }
    std::cout << std::flush;
}

void Tview::hline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem) {
    std::cout << "\e[" << x << ";" << y << "H";
    for(unsigned int i = 0; i < length; i++){
        std::cout << elem;
    }
    std::cout << "\e[m";
}

void Tview::vline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem) {
    std::cout << "\e[" << x << ";" << y << "H";
    for(unsigned int i = 0; i < length; i++){
        std::cout << elem;
        std::cout << "\e[" << x + i << ";" << y << "H";
    }
    std::cout << "\e[m";
}

void Tview::screen_clear(){
    printf("\e[1;1H \e[J");
}

Tview::~Tview() {
    screen_clear();
    tcsetattr(0, TCSANOW, &old_state);
    std::cout << "Goodbye!" << std::endl;
}
