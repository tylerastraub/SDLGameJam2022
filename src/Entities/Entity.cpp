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

SDL_Point Entity::getPosition() {
    return _position;
}