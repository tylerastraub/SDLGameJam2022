#ifndef GOAL_H
#define GOAL_H

#include "Entity.h"

class Goal : public Entity {
public:
    Goal(int x, int y);
    ~Goal() = default;
    
    void collisionEvent() override {};
    void tick(float timescale) override {};
    void render(int xOffset, int yOffset) override;

private:

};

#endif