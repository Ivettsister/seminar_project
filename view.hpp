#pragma once 

#include <functional>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <utility>
#include <memory>

using coords = std::pair<int, int>;

class View {


    protected:
    coords max_coords;
    std::function<void()> update_func;

    public:
    coords get_max_coord();
    void set_max_coord(int x, int y);
    static std::shared_ptr<View> get(const std::string arg = "text");
    static std::shared_ptr<View> obj;
    virtual void draw() = 0;
    virtual void run() = 0;
    virtual ~View();
    virtual void draw(coords& rabbit) = 0;
    void set_update(std::function<void()> f) {
        update_func = f;
    }
};
