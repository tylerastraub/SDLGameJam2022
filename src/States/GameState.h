#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Mouse.h"
#include "Tilemap.h"

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
    std::unique_ptr<Mouse> _mouse;
    Tilemap* _tilemap;

};

#endif