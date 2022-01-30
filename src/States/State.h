#ifndef STATE_H
#define STATE_H

#include <SDL.h>

class State {
public:
    State() = default;
    ~State() = default;

    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void handleMouseInput(SDL_Event e) = 0;
    virtual void tick(float timescale) = 0;
    virtual void render() = 0;

    void setNextState(State* nextState);
    void setGameSize(int w, int h);
    void setRenderer(SDL_Renderer* renderer);

    State* getNextState();
    SDL_Renderer* getRenderer();

protected:

private:
    State* _nextState = nullptr;
    SDL_Renderer* _renderer = nullptr;

    int _gameWidth = 0;
    int _gameHeight = 0;

};

#endif