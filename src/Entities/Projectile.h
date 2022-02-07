#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

#include <vector>

class Projectile : public Entity {
public:
    Projectile(int x, int y);
    ~Projectile() = default;

    void tick(float timescale) override;
    void render(int xOffset, int yOffset) override;

    bool isAtEndOfPath();

    void setPath(std::vector<SDL_Point> path);

private:
    std::vector<SDL_Point> _path;
    // What part of the projectile's path it is in
    float _pathIndex = 0.f;
    // Number of milliseconds to wait before advancing to next point in path
    float _moveSpeed = 4.f;
    // How many milliseconds it's been since the last update to position
    float _timeSinceLastMove = 0.f;
};

#endif