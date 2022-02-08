#ifndef LONG_RIGHT_TRIANGLE_H
#define LONG_RIGHT_TRIANGLE_H

#include "Object.h"

class LongRightTriangle : public Object {
public:
    LongRightTriangle();
    LongRightTriangle(ObjectDirection dir);
    ~LongRightTriangle() = default;

    void collisionEvent() override {};
    void render(int xOffset, int yOffset) override;

private:

};

#endif