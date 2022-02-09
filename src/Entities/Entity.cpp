#include "Entity.h"

Entity::Entity(int x, int y) {
    setEntityType(EntityType::ENTITY_NONE);
    _position = {x, y};
}

void Entity::kill() {
    setDead(true);
}

void Entity::setEntityType(EntityType type) {
    _entityType = type;
}

void Entity::setPosition(int x, int y) {
    _position = {x, y};
    _textureRect.x = x;
    _textureRect.y = y;
    _collisionRect.x = x + _rectOffset.x;
    _collisionRect.y = y + _rectOffset.y;
}

void Entity::setSpritesheet(Spritesheet* spritesheet) {
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

void Entity::setDead(bool isDead) {
    _dead = isDead;
}

void Entity::setDrawShadows(bool drawShadows) {
    _drawShadows = drawShadows;
}

EntityType Entity::getEntityType() {
    return _entityType;
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

Spritesheet* Entity::getSpritesheet() {
    return _entitySpritesheet;
}

bool Entity::isDead() {
    return _dead;
}

bool Entity::drawShadows() {
    return _drawShadows;
}