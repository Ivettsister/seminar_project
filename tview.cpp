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
        
        if (poll(&input, 1, 500) == 1){
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
    max_coord.first = win_size.ws_row + 1;
    max_coord.second = win_size.ws_col / 2;

    
}  

void Tview::draw() {
    struct winsize win_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size); 

    max_coord.first = win_size.ws_row;
    max_coord.second = win_size.ws_col; 

    screen_clear();

    hline(1, 1, max_coord.second, "\e[33m-");
    vline(2, 1, max_coord.first - 1, "\e[33m#");
    vline(2, max_coord.second, max_coord.first - 1, "\e[33m#");
    hline(max_coord.first, 1, max_coord.second, "\e[33m-");

    fflush(stdout);
}

void Tview::draw(coord& rabbit){
    std::cout << "\e[" << rabbit.first << ";" << rabbit.second * 2 - 1 << "H";
    std::cout << "\e[96m🐇";
}

void Tview::draw(coords& body, dir dir){

    for (auto segment : body) {
        std::cout << "\e[" << segment.first << ";" << segment.second * 2 - 1 << "H" << std::endl;    // goto xy
        if (segment == body.front()) {
                switch (dir) {
                case dir::RIGHT:
                    printf("\e[96m⇛ ");
                    break;
                case dir::UP:
                    printf("\e[96m⤊ ");
                    break;
                case dir::LEFT:
                    printf("\e[96m⇚ ");
                    break;
                case dir::DOWN:
                    printf("\e[96m⤋ ");
                    break;
                default:
                    printf("$");

                }
        }
        else printf("◉ ");
    }
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
