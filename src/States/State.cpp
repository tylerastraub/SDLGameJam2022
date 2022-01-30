#include "State.h"

void State::setNextState(State* nextState) {
    _nextState = nextState;
}

void State::setGameSize(int w, int h) {
    _gameWidth = w;
    _gameHeight = h;
}

void State::setRenderer(SDL_Renderer* renderer) {
    _renderer = renderer;
}

State* State::getNextState() {
    return _nextState;
}

SDL_Renderer* State::getRenderer() {
    return _renderer;
}