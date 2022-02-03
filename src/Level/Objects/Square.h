#ifndef SQUARE_H
#define SQUARE_H

#include "Object.h"

class Square : public Object {
public:
    Square();
    Square(ObjectDirection dir);

    void collisionEvent() override {};

private:

};

#endif