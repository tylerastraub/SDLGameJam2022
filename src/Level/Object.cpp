#include "Object.h"

Object::Object(ObjectDirection dir) {
    _direction = dir;
}

void Object::setDirection(ObjectDirection dir) {
    _direction = dir;
}

void Object::setObjectSpritesheet(Spritesheet spritesheet) {
    _objectSpritesheet = spritesheet;
}

std::list<Edge> Object::getEdges() {
    return _edges;
}

ObjectDirection Object::getDirection() {
    return _direction;
}

void Object::addEdge(Edge edge) {
    _edges.emplace_back(edge);
}