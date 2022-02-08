#include "Entity.h"

Entity::Entity(int x, int y) {
    _position = {x, y};
}

void Entity::setPosition(int x, int y) {
    _position = {x, y};
    _textureRect.x = x;
    _textureRect.y = y;
    _collisionRect.x = x + _rectOffset.x;
    _collisionRect.y = y + _rectOffset.y;
}

void Entity::setSpritesheet(Spritesheet spritesheet) {
    _entitySpritesheet = spritesheet;
}

void Entity::setCollisionRect(SDL_Rect rect) {
    _collisionRect = rect;
}

void Entity::setTextureRect(SDL_Rect rect) {
    _textureRect = rect;
}

void Entity::setRectOffset(int xOffset, int yOffset) {
    _rectOffset = {xOffset, yOffset};
}

SDL_Point Entity::getPosition() {
    return _position;
}

SDL_Rect Entity::getCollisionRect() {
    return _collisionRect;
}

SDL_Point Entity::getRectOffset() {
    return _rectOffset;
}