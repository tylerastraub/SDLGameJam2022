#include "Object.h"

Object::Object(ObjectDirection dir) {
    _direction = dir;
}

void Object::setPosition(int x, int y) {
    _position = {x, y};
}

void Object::setDirection(ObjectDirection dir) {
    _direction = dir;
}

void Object::setObjectSpritesheet(Spritesheet* spritesheet) {
    _objectSpritesheet = spritesheet;
}

SDL_Point Object::getPosition() {
    return _position;
}

std::list<Edge> Object::getEdges() {
    return _edges;
}

ObjectDirection Object::getDirection() {
    return _direction;
}

Spritesheet* Object::getSpritesheet() {
    return _objectSpritesheet;
}

void Object::addEdge(Edge edge) {
    _edges.emplace_back(edge);
}