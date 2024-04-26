#include "view.hpp"
#include "tview.hpp"
#include "gview.hpp"

std::shared_ptr<View> View::obj;
coord View::max_coord;

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
    return max_coord;
}

void View::set_max_coord(int x, int y){
    max_coord.first = x;
    max_coord.second = y;
}

View::~View() {

}
