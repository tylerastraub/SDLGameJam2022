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

void State::setRenderScale(int scale) {
    _renderScale = scale;
}

void State::setRenderer(SDL_Renderer* renderer) {
    _renderer = renderer;
}

void State::setTileset(Spritesheet* tileset) {
    _tileset = tileset;
}

void State::setText(TextSize size, Text* text) {
    switch(size) {
        case TextSize::SMALL:
            _smallText = text;
            break;
        case TextSize::MEDIUM:
            _mediumText = text;
            break;
        case TextSize::LARGE:
            _largeText = text;
            break;
        default:
            break;
    }
}

State* State::getNextState() {
    return _nextState;
}

SDL_Renderer* State::getRenderer() {
    return _renderer;
}

Spritesheet* State::getTileset() {
    return _tileset;
}

SDL_Point State::getGameSize() {
    return _gameSize;
}

SDL_Point State::getRenderSize() {
    return _renderSize;
}

int State::getRenderScale() {
    return _renderScale;
}

Text* State::getText(TextSize size) {
    switch(size) {
        case TextSize::SMALL:
            return _smallText;
            break;
        case TextSize::MEDIUM:
            return _mediumText;
            break;
        case TextSize::LARGE:
            return _largeText;
            break;
        default:
            return nullptr;
            break;
    }
}