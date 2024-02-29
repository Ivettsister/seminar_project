#include "game.hpp"
#include "control.hpp"
#include "view.hpp"

int main() {
    View* v = View::get("text");
    
    Game g(v);
    Control c(&g);

    c.get_user_input();
}