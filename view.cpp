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

coords View::get_max_coord(){
    return View::max_coords;
}

void View::set_max_coord(int x, int y){
    View::max_coords.first = x;
    View::max_coords.second = y;
}

View::~View() {

}

void View::draw(coords& rabbit) {
    std::cout << "\e[" << rabbit.first << ";" << rabbit.second * 2 - 1 << "H";
    std::cout << "\e[96m❂ ";
}
