#include "Projectile.h"

void Projectile::tick(float timescale) {
    _timeSinceLastMove += timescale / 1000.f;
    if(_timeSinceLastMove >= _moveSpeed) {
        _timeSinceLastMove = 0;
        if(_pathIndex < _path.size() - 1) ++_pathIndex;
    }
    setPosition(_path[_pathIndex].x, _path[_pathIndex].y);
}

void Projectile::render(int xOffset, int yOffset) {

}

void Projectile::setPath(std::vector<SDL_Point> path) {
    _path = path;
}