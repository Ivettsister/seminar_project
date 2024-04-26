#pragma once 

#include <functional>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <utility>
#include <memory>
#include <list>

const int fps = 3;

struct coord : public std::pair<int, int> {
    using base = std::pair<int, int>;
    using base::base;
    int dist(const coord& c) {
        return std::abs(c.first - first) + std::abs(c.second - second);
    }
};

using coords = std::list<coord>;


enum class dir {
        UP,
        LEFT,
        DOWN,
        RIGHT
};

class View {


    protected:
    static coord max_coord;
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
    virtual void draw(const coord& rabbit) = 0;
    virtual void draw(const coords& body, dir dir, int score) = 0;
    virtual void draw_score(int score) = 0;

    void set_update(std::function<void()> f) {
        update_func = f;
    }
    void set_on_key(std::function<void(int)> f) {
        key_func = f;
    }
};
