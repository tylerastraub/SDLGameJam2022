#ifndef OBJECT_H
#define OBJECT_H

#include "Edge.h"

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

    void setDirection(ObjectDirection dir);

    std::list<Edge> getEdges();
    ObjectDirection getDirection();

protected:
    void addEdge(Edge edge);

    // Hard coded because I'm too lazy to do a proper solution for this right now
    const int TILE_SIZE = 32;

private:
    std::list<Edge> _edges;
    
    ObjectDirection _direction = ObjectDirection::NORTH;

};

#endif