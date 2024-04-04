#include "view.hpp"

class Gview: public View {
    public:
    virtual void draw() override;
    virtual void draw(coord& rabbit) override;
    virtual void draw(coords& body, dir dir) override;
    virtual void run() override;
    Gview();
    ~Gview();
};