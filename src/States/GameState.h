#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Mouse.h"
#include "Tilemap.h"
#include "CollisionDetector.h"
#include "Projectile.h"

#include <memory>

class GameState : public State {
public:
    GameState() = default;
    ~GameState() = default;

    void init() override;
    void handleInput() override;
    void handleMouseInput(SDL_Event e) override;
    void tick(float timescale) override;
    void render() override;

    void addEntity(std::shared_ptr<Entity> entity);

private:
    std::unique_ptr<Mouse> _mouse = nullptr;
    std::unique_ptr<Tilemap> _tilemap = nullptr;
    std::unique_ptr<Grid> _grid = nullptr;
    CollisionDetector _collisionDetector;

    // The path displayed for the guide line
    std::vector<SDL_Point> _guideLineShotPath;
    // The actual path the bullet will take
    std::vector<SDL_Point> _shotPath;
    // How many bounces to display for guide line
    int _numOfGuideLineBounces = 1;
    // How many bounces the shot should actually do
    int _numOfBounces = 10;

    Projectile* _shot = nullptr;
    SDL_Point _shotStart = {336, 180};
};

#endif