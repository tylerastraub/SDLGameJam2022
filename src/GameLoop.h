#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "State.h"

#include <SDL.h>
#include <memory>

class GameLoop {
public:
    GameLoop() = default;
    ~GameLoop();

    bool init();
    bool loadResources();
    void startLoop();
    void exit();

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    // The logical width of the game
    const int GAME_WIDTH = 320;
    // The logical height of the game
    const int GAME_HEIGHT = 180;
    // The width of the screen. Note that this should be scaled based on GAME_WIDTH
    const int SCREEN_WIDTH = 1280;
    // The height of the screen. Note that this should be scaled based on GAME_HEIGHT
    const int SCREEN_HEIGHT = 720;

    bool _exitFlag = false;

    State* _currentState = nullptr;
};

#endif