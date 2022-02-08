#include "Projectile.h"

#include <iostream>

Projectile::Projectile(int x, int y) {
    setEntityType(EntityType::PROJECTILE);
    SDL_Rect collisionRect = {0, 0, 1, 1};
    SDL_Rect textureRect = {0, 0, 3, 3};
    setCollisionRect(collisionRect);
    setTextureRect(textureRect);
    setRectOffset(1, 1);
    setPosition(x - 1, y - 1);
}

void Projectile::tick(float timescale) {
    _pathIndex += timescale * 1000.f / _moveSpeed;
    if(_pathIndex >= _path.size()) _pathIndex = _path.size() - 1;
    setPosition(_path[(int) _pathIndex].x - 1, _path[(int) _pathIndex].y - 1);
}

void Projectile::render(int xOffset, int yOffset) {

}

void Projectile::kill() {
    setDead(true);
}

bool Projectile::isAtEndOfPath() {
    if((int) _pathIndex >= _path.size() - 1) return true;
    return false;
}

void Projectile::setPath(std::vector<SDL_Point> path) {
    _path = path;
}