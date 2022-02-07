#include "Projectile.h"

#include <iostream>

Projectile::Projectile(int x, int y) {
    setPosition(x, y);
}

void Projectile::tick(float timescale) {
    std::cout << _pathIndex << std::endl;
    _pathIndex += timescale * 1000.f / _moveSpeed;
    if(_pathIndex >= _path.size()) _pathIndex = _path.size() - 1;
    setPosition(_path[(int) _pathIndex].x, _path[(int) _pathIndex].y);
}

void Projectile::render(int xOffset, int yOffset) {

}

bool Projectile::isAtEndOfPath() {
    if((int) _pathIndex >= _path.size() - 1) return true;
    return false;
}

void Projectile::setPath(std::vector<SDL_Point> path) {
    _path = path;
}