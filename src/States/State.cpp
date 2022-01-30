#include "State.h"

void State::setNextState(State* nextState) {
    _nextState = nextState;
}

void State::setGameSize(int w, int h) {
    _gameSize = {w, h};
}

void State::setRenderSize(int w, int h) {
    _renderSize = {w, h};
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

SDL_Point State::getGameSize() {
    return _gameSize;
}

SDL_Point State::getRenderSize() {
    return _renderSize;
}