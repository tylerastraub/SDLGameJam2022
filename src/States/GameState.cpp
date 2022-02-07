#include "GameState.h"

#include <iostream>
#include <chrono>
#include <algorithm>

/**
 * TODO:
 * - Add a couple more basic objects, then add essential game entities (exit, bullet, etc.)
 */

void GameState::init() {
    SDL_Point gameSize = getGameSize();
    SDL_Point renderSize = getRenderSize();
    _mouse = std::make_unique<Mouse>(
        (float) renderSize.x / (float) gameSize.x, (float) renderSize.y / (float) gameSize.y);

    std::vector<std::vector<int>> testMap = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 4, 0, 0, 1},
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 5, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    _tilemap = std::make_unique<Tilemap>(testMap);
    _grid = std::make_unique<Grid>(_tilemap->getGrid());
    _tilemap->printTilemap();

    _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _mouse->getMousePos(), _numOfGuideLineBounces);
    _shotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _mouse->getMousePos(), _numOfBounces);
}

void GameState::handleInput() {}

void GameState::handleMouseInput(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        _mouse->setPos(x, y);
        _mouse->setMouseMoved(true);
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN) {
        _mouse->setMouseMoved(false);
        if(e.button.button == SDL_BUTTON_LEFT) {
            _mouse->setLeftButtonDown(true);
        }
        else if(e.button.button == SDL_BUTTON_RIGHT) {
            _mouse->setRightButtonDown(true);
        } 
    }
    else if(e.type == SDL_MOUSEBUTTONUP) {
        _mouse->setMouseMoved(false);
        if(e.button.button == SDL_BUTTON_LEFT) {
            _mouse->setLeftButtonDown(false);
        }
        else if(e.button.button == SDL_BUTTON_RIGHT) {
            _mouse->setRightButtonDown(false);
        } 
    }
    else {
        _mouse->setMouseMoved(false);
    }
}

void GameState::tick(float timescale) {
    if(_mouse->mouseMoved()) {
        _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _mouse->getMousePos(), _numOfGuideLineBounces);
    }

    if(_shot) {
        if(_shot->isAtEndOfPath()) {
            delete _shot;
            _shot = nullptr;
        }
        else {
            _shot->tick(timescale);
        }
    }
    if(_mouse->isLeftButtonDown()) {
        if(_shot) delete _shot;
        _shotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _mouse->getMousePos(), _numOfBounces);
        auto s = _shotPath.begin();
        _shot = new Projectile(s->x, s->y);
        _shot->setPath(_shotPath);
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
                    break;
                }
                case TileType::RIGHT_TRIANGLE_NORTH:
                case TileType::RIGHT_TRIANGLE_EAST:
                case TileType::RIGHT_TRIANGLE_SOUTH:
                case TileType::RIGHT_TRIANGLE_WEST:
                case TileType::DIAMOND:
                case TileType::LONG_RIGHT_TRIANGLE_NORTH:
                case TileType::LONG_RIGHT_TRIANGLE_EAST:
                case TileType::LONG_RIGHT_TRIANGLE_SOUTH:
                case TileType::LONG_RIGHT_TRIANGLE_WEST: {
                    SDL_SetRenderDrawColor(getRenderer(), 0x87, 0x87, 0x87, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
                }
                default:
                    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0xFF, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
            }
            // DEBUG: draw all collision edges (hitboxes)
            std::list<Edge> edges = _grid->getEdges(x, y);
            for(Edge e : edges) {
                SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0x00, 0xAF);
                SDL_RenderDrawLine(getRenderer(), e.p1.x, e.p1.y, e.p2.x, e.p2.y);
            }
        }
    }

    // Render shot path
    // auto clock = std::chrono::high_resolution_clock::now();
    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0x00, 0xAF);
    for(auto point : _guideLineShotPath) {
        SDL_RenderDrawPoint(getRenderer(), point.x, point.y);
    }
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - clock).count() << "ms" << std::endl;

    if(_shot) {
        SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_Rect r = {_shot->getPosition().x - 1, _shot->getPosition().y - 1, 3, 3};
        SDL_RenderDrawRect(getRenderer(), &r);
    }

    SDL_RenderPresent(getRenderer());
}