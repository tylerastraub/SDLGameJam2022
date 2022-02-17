#ifndef STATE_H
#define STATE_H

#include "Spritesheet.h"
#include "Text.h"

#include <SDL.h>

enum TextSize {
    SMALL = 0,
    MEDIUM = 1,
    LARGE = 2,
};

class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void handleMouseInput(SDL_Event e) = 0;
    virtual void tick(float timescale) = 0;
    virtual void render() = 0;

    void setNextState(State* nextState);
    void setGameSize(int w, int h);
    void setRenderSize(int w, int h);
    void setRenderScale(int scale);
    void setRenderer(SDL_Renderer* renderer);
    void setTileset(Spritesheet* tileset);
    void setText(TextSize size, Text* text);

    State* getNextState();
    SDL_Renderer* getRenderer();
    Spritesheet* getTileset();
    SDL_Point getGameSize();
    SDL_Point getRenderSize();
    int getRenderScale();
    Text* getText(TextSize size);

protected:

private:
    State* _nextState = nullptr;
    SDL_Renderer* _renderer = nullptr;
    Spritesheet* _tileset = nullptr;

    SDL_Point _gameSize;
    SDL_Point _renderSize;
    int _renderScale;
    
    // Text
    Text* _smallText = nullptr;
    Text* _mediumText = nullptr;
    Text* _largeText = nullptr;
};

#endif