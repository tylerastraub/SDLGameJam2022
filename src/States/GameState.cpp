#include "GameState.h"

#include <iostream>
#include <chrono>
#include <algorithm>

/**
 * TODO:
 * - Fix little gaps between objects causing collision issues (could just cheat and make each square edge 1 pixel longer, then make tilemap slightly bigger to avoid out of bounds exceptions?)
 * - Fix shot sometimes just going through walls (think this has to do with magnitude being too great?)
 * - Fix bug where going perpendicular to wall lets you pass through it
 * - Once angle calculations and bounces/whatnot are looking clean, move to adding a couple more basic objects, then add essential game entities (exit, bullet, etc.)
 */

void GameState::init() {
    SDL_Point gameSize = getGameSize();
    SDL_Point renderSize = getRenderSize();
    _mouse = std::make_unique<Mouse>(
        (float) renderSize.x / (float) gameSize.x, (float) renderSize.y / (float) gameSize.y);

    std::vector<std::vector<int>> testMap = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 1},
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    _tilemap = std::make_unique<Tilemap>(testMap);
    _grid = std::make_unique<Grid>(_tilemap->getGrid());
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

void GameState::tick(float timescale) {
    _shotPath = _collisionDetector.calculateShotPath(*_grid, {336, 180}, _mouse->getMousePos(), 4);
    if(_mouse->isLeftButtonDown()) {
        std::cout << "click" << std::endl;
    }
}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    // Render level
    const int tileSize = _tilemap->getTileSize();
    for(int x = 0; x < _tilemap->getTilemapWidth(); ++x) {
        for(int y = 0; y < _tilemap->getTilemapHeight(); ++y) {
            SDL_Rect tile = {x * tileSize, y * tileSize, tileSize, tileSize};
            switch(_tilemap->getTile(x, y)) {
                case TileType::EMPTY:
                    SDL_SetRenderDrawColor(getRenderer(), 0x45, 0x45, 0x45, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
                case TileType::SQUARE: {
                    SDL_SetRenderDrawColor(getRenderer(), 0x87, 0x87, 0x87, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    std::list<Edge> edges = _grid->getEdges(x, y);
                    for(Edge e : edges) {
                        SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0x00, 0xAF);
                        SDL_RenderDrawLine(getRenderer(), e.p1.x, e.p1.y, e.p2.x, e.p2.y);
                    }
                    break;
                }
                case TileType::RIGHT_TRIANGLE_NORTH:
                case TileType::RIGHT_TRIANGLE_EAST:
                case TileType::RIGHT_TRIANGLE_SOUTH:
                case TileType::RIGHT_TRIANGLE_WEST:
                case TileType::DIAMOND: {
                    SDL_SetRenderDrawColor(getRenderer(), 0x87, 0x87, 0x87, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    std::list<Edge> edges = _grid->getEdges(x, y);
                    for(Edge e : edges) {
                        SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0x00, 0xAF);
                        SDL_RenderDrawLine(getRenderer(), e.p1.x, e.p1.y, e.p2.x, e.p2.y);
                    }
                    break;
                }
                default:
                    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0xFF, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
            }
        }
    }

    // Render shot path
    // auto clock = std::chrono::high_resolution_clock::now();
    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0x00, 0xAF);
    for(auto point : _shotPath) {
        SDL_RenderDrawPoint(getRenderer(), point.x, point.y);
    }
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - clock).count() << "ms" << std::endl;

    SDL_RenderPresent(getRenderer());
}