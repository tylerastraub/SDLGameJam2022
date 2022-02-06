#ifndef ENTITY_H
#define ENTITY_H

#include "Spritesheet.h"

#include <SDL.h>

class Entity {
public:
    Entity(int x, int y);
    ~Entity() = default;

    virtual void tick(float timescale) = 0;
    virtual void render(int xOffset, int yOffset) = 0;

    void setPosition(int x, int y);
    void setSpritesheet(Spritesheet spritesheet);

private:
    SDL_Point _position = {0, 0};
    // The rect used for collision calculations with other entities
    SDL_Rect _collisionRect = {0, 0, 0, 0};
    // The rect mapped to the entity's texture
    SDL_Rect _textureRect = {0, 0, 0, 0};
    // The difference between the texture rect and collision rect. For instance,
    // if _textureRect is at (20, 10), and _rectOffset is (4, 6), then _collisionRect
    // will automatically be at (24, 16);
    SDL_Point _rectOffset = {0, 0};

    Spritesheet _entitySpritesheet;
};

#endif