#ifndef SQUARE_H
#define SQUARE_H

#include "Object.h"

class Square : public Object {
public:
    Square();
    Square(ObjectDirection dir);
    ~Square() = default;

    void collisionEvent() override {};
    void render(int xOffset, int yOffset) override {};

private:

};

#endif