#include "GameState.h"

void GameState::init() {}

void GameState::handleInput() {}

void GameState::tick(float timescale) {}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    SDL_RenderPresent(getRenderer());
}