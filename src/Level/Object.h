#ifndef OBJECT_H
#define OBJECT_H

#include "Edge.h"
#include "Spritesheet.h"

#include <list>

enum ObjectDirection {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class Object {
public:
    Object() = default;
    Object(ObjectDirection dir);
    ~Object() = default;

    // Method called upon object colliding with shot
    virtual void collisionEvent() = 0;
    virtual void render(int xOffset, int yOffset) = 0;

    void setPosition(int x, int y);
    void setDirection(ObjectDirection dir);
    void setObjectSpritesheet(Spritesheet* spritesheet);
    void setDrawShadows(bool drawShadows);

    SDL_Point getPosition();
    std::list<Edge> getEdges();
    ObjectDirection getDirection();
    Spritesheet* getSpritesheet();
    bool drawShadows();

protected:
    void addEdge(Edge edge);

    // Hard coded because I'm too lazy to do a proper solution for this right now
    const int TILE_SIZE = 32;

private:
    SDL_Point _position = {0, 0};
    std::list<Edge> _edges;
    
    ObjectDirection _direction = ObjectDirection::NORTH;
    Spritesheet* _objectSpritesheet;

    bool _drawShadows = true;

};

#endif