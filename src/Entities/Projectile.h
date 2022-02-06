#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

#include <vector>

class Projectile : public Entity {
public:
    Projectile() = default;
    ~Projectile() = default;

    void tick(float timescale) override;
    void render(int xOffset, int yOffset) override;

    void setPath(std::vector<SDL_Point> path);

private:
    std::vector<SDL_Point> _path;
    // What part of the projectile's path it is in
    int _pathIndex = 0;
    // Number of milliseconds to wait before advancing to next point in path
    int _moveSpeed = 10;
    // How many milliseconds it's been since the last update to position
    int _timeSinceLastMove = 0;
};

#endif