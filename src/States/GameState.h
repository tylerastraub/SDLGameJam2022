#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Mouse.h"

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
    Mouse _mouse;

};

#endif