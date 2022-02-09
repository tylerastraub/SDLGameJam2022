#include "Goal.h"

Goal::Goal(int x, int y) {
    setEntityType(EntityType::GOAL_ENTITY);
    setCollisionRect({0, 0, 32, 32});
    setTextureRect({0, 0, 32, 32});
    setPosition(x, y);
}

void Goal::collisionEvent() {
    _isHit = true;
}

void Goal::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(32);
    s->setTileHeight(32);
    s->setRenderWidth(32);
    s->setRenderHeight(32);
    if(drawShadows()) {
        s->setTileIndex(7, 0);
        s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2);
    }
    int xTileIndex = (_isHit) ? 6 : 5;
    s->setTileIndex(xTileIndex, 0);
    s->render(getPosition().x + xOffset, getPosition().y + yOffset);
}

bool Goal::isHit() {
    return _isHit;
}