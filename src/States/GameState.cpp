#include "GameState.h"

#include <iostream>
#include <chrono>
#include <algorithm>

void GameState::init() {
    SDL_Point gameSize = getGameSize();
    SDL_Point renderSize = getRenderSize();
    _mouse = std::make_unique<Mouse>(
        (float) renderSize.x / (float) gameSize.x, (float) renderSize.y / (float) gameSize.y);

    std::vector<std::vector<int>> testMap = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
    _shotPath = _collisionDetector.calculateShotPath(*_grid, {336, 180}, _mouse->getMousePos(), 0);
    if(_mouse->isLeftButtonDown()) {
        std::cout << "click" << std::endl;
    }
}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());
    
    SDL_Point start = {-1, -1};
    SDL_Point end = {-1, -1};
    if(!_shotPath.empty()) {
        start = _shotPath[0];
        end = _shotPath[_shotPath.size() - 1];
    }

    const int tileSize = _tilemap->getTileSize();
    std::vector<SDL_Point> intersectingCells = _grid->getGridCellsIntersectingWithLine(start, end);
    // auto clock = std::chrono::high_resolution_clock::now();
    for(int x = 0; x < _tilemap->getTilemapWidth(); ++x) {
        for(int y = 0; y < _tilemap->getTilemapHeight(); ++y) {
            SDL_Rect tile = {x * tileSize, y * tileSize, tileSize, tileSize};
            switch(_tilemap->getTile(x, y)) {
                case TileType::EMPTY:
                    SDL_SetRenderDrawColor(getRenderer(), 0x45, 0x45, 0x45, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
                case TileType::SOLID: {
                    SDL_SetRenderDrawColor(getRenderer(), 0x87, 0x87, 0x87, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    std::list<Edge> edges = _grid->getEdges(x, y);
                    for(Edge e : edges) {
                        SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0x00, 0xAF);
                        SDL_RenderDrawLine(getRenderer(), e.p1.x, e.p1.y, e.p2.x, e.p2.y);
                    }
                    break;
                }
                case TileType::SPECIAL: {
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
                    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0xFF, 0xFF, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
            }
        }
    }
    for(SDL_Point cell : intersectingCells) {
        SDL_Rect tile = {cell.x * tileSize, cell.y * tileSize, tileSize, tileSize};
        SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0xFF, 0x8F);
        SDL_RenderFillRect(getRenderer(), &tile);
    }
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - clock).count() << "ms" << std::endl;

    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0x00, 0xAF);
    for(auto point : _shotPath) {
        SDL_RenderDrawPoints(getRenderer(), _shotPath.data(), _shotPath.size());
    }
    // SDL_RenderDrawLine(getRenderer(), start.x, start.y, end.x, end.y);

    SDL_RenderPresent(getRenderer());
}