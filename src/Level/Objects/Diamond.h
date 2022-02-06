#ifndef DIAMOND_H
#define DIAMOND_H

#include "Object.h"

class Diamond : public Object {
public:
    Diamond();
    Diamond(ObjectDirection dir);
    ~Diamond() = default;

    void collisionEvent() override {};
    void render(int xOffset, int yOffset) override {};

private:

};

#endif