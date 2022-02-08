#ifndef RIGHT_TRIANGLE_H
#define RIGHT_TRIANGLE_H

#include "Object.h"

class RightTriangle : public Object {
public:
    RightTriangle();
    RightTriangle(ObjectDirection dir);
    ~RightTriangle() = default;

    void collisionEvent() override {};
    void render(int xOffset, int yOffset) override;

private:

};

#endif