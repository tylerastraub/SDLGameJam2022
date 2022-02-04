#ifndef DIAMOND_H
#define DIAMOND_H

#include "Object.h"

class Diamond : public Object {
public:
    Diamond();
    Diamond(ObjectDirection dir);

    void collisionEvent() override {};

private:

};

#endif