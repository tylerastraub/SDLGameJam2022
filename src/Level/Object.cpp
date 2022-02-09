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

void Object::setDrawShadows(bool drawShadows) {
    _drawShadows = drawShadows;
}

void Object::setNaturalSize(int w, int h) {
    _naturalSize = {w, h};
}

void Object::setRenderSize(int w, int h) {
    _renderSize = {w, h};
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

bool Object::drawShadows() {
    return _drawShadows;
}

SDL_Point Object::getNaturalSize() {
    return _naturalSize;
}

SDL_Point Object::getRenderSize() {
    return _renderSize;
}

void Object::addEdge(Edge edge) {
    _edges.emplace_back(edge);
}