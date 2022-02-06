#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Mouse.h"
#include "Tilemap.h"
#include "CollisionDetector.h"

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

private:
    std::unique_ptr<Mouse> _mouse = nullptr;
    std::unique_ptr<Tilemap> _tilemap = nullptr;
    std::unique_ptr<Grid> _grid = nullptr;
    CollisionDetector _collisionDetector;

    std::vector<SDL_Point> _shotPath;
    int _numOfBounces = 4;
};

#endif