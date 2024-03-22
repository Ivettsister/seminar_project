#include "view.hpp"

class Gview: public View {
    public:
    virtual void draw() override;
    virtual void draw(coords& rabbit) override;
    virtual void run() override;
    Gview();
    ~Gview();
};