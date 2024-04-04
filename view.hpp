#pragma once 

#include <functional>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <utility>
#include <memory>
#include <list>

using coord = std::pair<int, int>;
using coords = std::list<coord>;

enum class dir {
        UP,
        LEFT,
        DOWN,
        RIGHT
};

class View {


    protected:
    coord max_coord;
    std::function<void()> update_func;
    std::function<void(int)> key_func;

    public:
    coord get_max_coord();
    void set_max_coord(int x, int y);
    static std::shared_ptr<View> get(const std::string arg = "text");
    static std::shared_ptr<View> obj;
    virtual void run() = 0;
    virtual ~View();

    virtual void draw() = 0;
    virtual void draw(coord& rabbit) = 0;
    virtual void draw(coords& body, dir dir) = 0;

    void set_update(std::function<void()> f) {
        update_func = f;
    }
    void set_on_key(std::function<void(int)> f) {
        key_func = f;
    }
};
