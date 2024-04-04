#include "view.hpp"
#include "tview.hpp"
#include "gview.hpp"

std::shared_ptr<View> View::obj;

std::shared_ptr<View> View::get(std::string s) {
    if (obj) return obj;
    if (s == "text") {
        obj = std::make_shared<Tview>();
    }
    else {
        obj = std::make_shared<Gview>();
    }
    return obj;
}

coord View::get_max_coord(){
    return View::max_coord;
}

void View::set_max_coord(int x, int y){
    View::max_coord.first = x;
    View::max_coord.second = y;
}

View::~View() {

}

/*void View::draw(coord& rabbit) {
    std::cout << "\e[" << rabbit.first << ";" << rabbit.second * 2 - 1 << "H";
    std::cout << "\e[96m❂";
}*/


