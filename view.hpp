#pragma once 

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>

class View {
    public:
    static View* view;
    static View* get(std::string s = "text");
    virtual void draw() = 0;
    virtual ~View();
};

class Tview: public View {
    private:
    void clear_window();
    void set_colors(int brightness, int color);
    void gotoxy(int x, int y);
    void puts(std::string s);

    public:
    virtual void draw();
};

class Gview: public View {
    virtual void draw();
};