#pragma once 

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <utility>
#include <memory>
#include "tview.hpp"
#include "gview.hpp"
#include "game.hpp"

using coords = std::pair<int, int>;

class View {
    protected:
    coords max_coords;

    public:
    static View* view;
    coords get_max_coord();
    void set_max_coord(int x, int y);
    static std::shared_ptr<View> get(const std::string arg = "text");
    static std::shared_ptr<View> obj;
    virtual void draw() = 0;
    virtual void run() = 0;
    virtual ~View();
    std::function<void(void)> draw_all;
    virtual void draw(coords& rabbit) = 0;
};
