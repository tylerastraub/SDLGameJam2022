#ifndef ENTITY_H
#define ENTITY_H

#include "Spritesheet.h"

#include <SDL.h>

enum EntityType {
    NONE = 0,
    PROJECTILE = 1,
    GOAL_ENTITY = 2,
};

class Entity {
public:
    Entity() = default;
    Entity(int x, int y);
    ~Entity() = default;

    // Method called upon collision with entity or object
    virtual void collisionEvent() = 0;
    virtual void tick(float timescale) = 0;
    virtual void render(int xOffset, int yOffset) = 0;
    virtual void kill();

    void setEntityType(EntityType type);
    void setPosition(int x, int y);
    void setSpritesheet(Spritesheet* spritesheet);
    void setCollisionRect(SDL_Rect rect);
    void setTextureRect(SDL_Rect rect);
    void setRectOffset(int xOffset, int yOffset);
    void setDead(bool isDead);
    void setDrawShadows(bool drawShadows);

    EntityType getEntityType();
    SDL_Point getPosition();
    SDL_Rect getCollisionRect();
    SDL_Point getRectOffset();
    Spritesheet* getSpritesheet();
    bool isDead();
    bool drawShadows();

private:
    EntityType _entityType = EntityType::NONE;
    SDL_Point _position = {0, 0};
    // The rect used for collision calculations with other entities
    SDL_Rect _collisionRect = {0, 0, 0, 0};
    // The rect mapped to the entity's texture
    SDL_Rect _textureRect = {0, 0, 0, 0};
    // The difference between the texture rect and collision rect. For instance,
    // if _textureRect is at (20, 10), and _rectOffset is (4, 6), then _collisionRect
    // will automatically be at (24, 16);
    SDL_Point _rectOffset = {0, 0};

    Spritesheet* _entitySpritesheet;

    // Whether or not the entity is dead. Usually used to signify entity is ready to be deleted
    bool _dead = false;

    bool _drawShadows = true;
};

#endif