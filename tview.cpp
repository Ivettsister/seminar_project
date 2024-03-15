#include <sys/ioctl.h>
#include <signal.h>
#include <termios.h>
#include "tview.hpp"

void Tview::draw() {
        
}

void Tview::run() {
    
}

Tview::Tview() {
    /* main part*/
}

void Tview::draw_frame() {
    struct winsize win_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size); 

    max_coords.first = win_size.ws_row;
    max_coords.second = win_size.ws_col;

    screen_clear();

    hline(1, 1, max_coords.second, "\e[33m-");
    vline(2, 1, max_coords.first - 1, "\e[33m#");
    vline(2, max_coords.second, max_coords.first - 1, "\e[33m#");
    hline(max_coords.first, 1, max_coords.second, "\e[33m-");

    fflush(stdout);
}

void Tview::draw(coords& rabbit){
    printf("\e[%d;%dH", rabbit.first, rabbit.second * 2 - 1);
    printf("\e[96m❂ ");
}

void Tview::hline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem) {
    printf("\e[%d;%dH", x, y);
    for(unsigned int i = 0; i < length; i++){
        std::cout << elem;
    }
    std::cout << "\e[m";
}

void Tview::vline(unsigned int x, unsigned int y, unsigned int length, const std::string& elem) {
    printf("\e[%d;%dH", x, y);
    for(unsigned int i = 0; i < length; i++){
        std::cout << elem;
        printf("\e[%d;%dH", x + i, y);
    }
    std::cout << "\e[m";
}

void Tview::screen_clear(){
    printf("\e[1;1H \e[J");
}

void Tview::draw(coords& rabbit) {
        
}
