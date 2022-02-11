#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "State.h"
#include "Spritesheet.h"
#include "Text.h"

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
    const int GAME_WIDTH = 640;
    // The logical height of the game
    const int GAME_HEIGHT = 360;
    // The render scale for the window
    const int RENDER_SCALE = 3;

    bool _exitFlag = false;

    State* _currentState = nullptr;
    std::unique_ptr<Spritesheet> _tileSpritesheet = nullptr;
    
    // Text
    const char * _fontPath = "res/font/Munro.ttf";
    int _smallTextSize = 10;
    std::unique_ptr<Text> _smallText = nullptr;
    int _mediumTextSize = 14;
    std::unique_ptr<Text> _mediumText = nullptr;
    int _largeTextSize = 18;
    std::unique_ptr<Text> _largeText = nullptr;
};

#endif