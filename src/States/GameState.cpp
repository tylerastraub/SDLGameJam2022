#include "GameState.h"

#include <iostream>

void GameState::init() {
    SDL_Point gameSize = getGameSize();
    SDL_Point renderSize = getRenderSize();
    _mouse = std::make_unique<Mouse>(
        (float) renderSize.x / (float) gameSize.x, (float) renderSize.y / (float) gameSize.y);

    std::vector<std::vector<int>> testMap = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    _tilemap = new Tilemap(testMap);
    _tilemap->printTilemap();
}

void GameState::handleInput() {}

void GameState::handleMouseInput(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        _mouse->setPos(x, y);
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN) {
        if(e.button.button == SDL_BUTTON_LEFT) {
            _mouse->setLeftButtonDown(true);
        }
        else if(e.button.button == SDL_BUTTON_RIGHT) {
            _mouse->setRightButtonDown(true);
        } 
    }
    else if(e.type == SDL_MOUSEBUTTONUP) {
        if(e.button.button == SDL_BUTTON_LEFT) {
            _mouse->setLeftButtonDown(false);
        }
        else if(e.button.button == SDL_BUTTON_RIGHT) {
            _mouse->setRightButtonDown(false);
        } 
    }
}

void GameState::tick(float timescale) {}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    const int tileSize = _tilemap->getTileSize();
    for(int x = 0; x < _tilemap->getTilemapWidth(); ++x) {
        for(int y = 0; y < _tilemap->getTilemapHeight(); ++y) {
            switch(_tilemap->getTile(x, y)) {
                case TileType::EMPTY:
                    SDL_SetRenderDrawColor(getRenderer(), 0x45, 0x45, 0x45, 0xFF);
                    break;
                case TileType::SOLID:
                    SDL_SetRenderDrawColor(getRenderer(), 0x87, 0x87, 0x87, 0xFF);
                    break;
                default:
                    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0xFF, 0xFF, 0xFF);
                    break;
            }
            SDL_Rect tile = {x * tileSize, y * tileSize, tileSize, tileSize};
            SDL_RenderFillRect(getRenderer(), &tile);
        }
    }

    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0x00, 0xAF);
    SDL_RenderDrawLine(getRenderer(), 50, 50, _mouse->getMouseX(), _mouse->getMouseY());

    SDL_RenderPresent(getRenderer());
}