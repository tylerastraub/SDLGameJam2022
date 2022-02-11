#include "GameState.h"
#include "Goal.h"
#include "ShopButton.h"
#include "LevelLoader.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <cmath>

/**
 * TODO:
 * - Add next level button
 * - Actually create levels lol
 * - IF HAVE TIME - Add sound + menu
 */

void GameState::init() {
    // Hardware init
    SDL_Point gameSize = getGameSize();
    SDL_Point renderSize = getRenderSize();
    _mouse = std::make_unique<Mouse>(
        (float) renderSize.x / (float) gameSize.x, (float) renderSize.y / (float) gameSize.y);

    // Tilemap init
    // std::vector<std::vector<int>> testMap = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 3, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 4, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 2, 0, 0, 0, 0, 7, 0, 0, 12, 0, 0, 0, 6, 0, 11, 0, 0, 0, 1},
    //     {1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 5, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    // };

    // Load levels
    _levels = {
        "res/level/test_level.txt"
    };
    std::vector<std::vector<int>> levelMap = LevelLoader::loadLevel("res/level/test_level.txt");
    _tilemap = std::make_unique<Tilemap>(getTileset(), levelMap);
    _defaultTilemap = levelMap;
    _grid = std::make_unique<Grid>(_tilemap->getGrid());
    _shotStart = _tilemap->getStart();
    _shotTarget = {_shotStart.x, 0};

    // Shot init
    _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, 0);
    _shotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, _numOfBounces);

    // Shop init
    _shop = std::make_unique<Shop>();
    _shop->setSpritesheet(getTileset());
    for(auto bb : _shop->getObjectBuyButtons()) {
        ObjectClickable* oc = (ObjectClickable*) bb.get();
        oc->setShop(_shop.get());
    }

    // Clickables init
    std::shared_ptr<ShopButton> shopButton = std::make_shared<ShopButton>();
    shopButton->setPosition(4, 16);
    shopButton->setSpritesheet(getTileset());
    shopButton->setShop(_shop.get());
    _clickables.emplace_back(shopButton);
    
    _resetButton = std::make_shared<ResetButton>();
    _resetButton->setPosition(24, 16);
    _resetButton->setSpritesheet(getTileset());
    _resetButton->setShop(_shop.get());
    _clickables.emplace_back(_resetButton);

    _nextLevelButton = std::make_shared<NextLevelButton>();
    _nextLevelButton->setPosition(44, 16);
    _nextLevelButton->setSpritesheet(getTileset());
    _nextLevelButton->setShop(_shop.get());
    _clickables.emplace_back(_nextLevelButton);
}

void GameState::handleInput() {
    _lastFramePressingR = _pressingR;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    _pressingR = currentKeyStates[SDL_SCANCODE_R];
}

void GameState::handleMouseInput(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        _mouse->setPos(x - _renderOffset.x * getRenderScale(), y - _renderOffset.y * getRenderScale());
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
    if(!_mouse->isLeftButtonDown()) {
        _mouseIsAiming = false;
        _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, 0);
    }

    if(_resetButton->requestsReset()) {
        _resetButton->setsRequestsReset(false);
        _tilemap = std::make_unique<Tilemap>(getTileset(), _defaultTilemap);
        _grid = std::make_unique<Grid>(_tilemap->getGrid());
        _shop->resetMoney();
        _shotTarget = {_shotStart.x, 0};
        _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, 0);
        if(_shot) _shot->kill();
        _shot = nullptr;
        _currentObjSelection = nullptr;
        _currentOC = nullptr;
    }

    if(_mouse->isLeftButtonDown() && !_currentObjSelection) {
        SDL_Point mouseTarget = _mouse->getMousePos();
        std::vector<SDL_Point> singleShot = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, 0);
        if(_collisionDetector.mouseCollidingWithShot(_mouse.get(), singleShot) || _mouseIsAiming) {
            _mouseIsAiming = true;
            SDL_Point mouseDelta = {mouseTarget.x - _shotStart.x, mouseTarget.y - _shotStart.y};
            float magnitude = (float) _grid->getGridWidth() * _grid->getTileSize() / std::hypot(mouseDelta.x, mouseDelta.y);
            _shotTarget = {(int) (_shotStart.x + mouseDelta.x * magnitude), (int) (_shotStart.y + mouseDelta.y * magnitude)};
            _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, _numOfGuideLineBounces);
        }
    }

    for(auto ent : _grid->getEntities()) {
        ent->tick(timescale);
        if(ent->getEntityType() == EntityType::GOAL_ENTITY) {
            Goal g = *((Goal*) ent.get());
            if(g.isHit()){
                if(_shot) _shot->kill();
                _nextLevelButton->setEnabled(true);
            } 
        }
    }

    if(_shot) {
        if(_shot->isAtEndOfPath() || _shot->isDead()) {
            delete _shot;
            _shot = nullptr;
        }
        else {
            _shot->tick(timescale);
            _collisionDetector.checkForShotEntityCollisions(_shot, _grid->getEntities());
        }
    }
    if(_mouse->isRightButtonDown() && !_nextLevelButton->isEnabled()) {
        if(_shot) delete _shot;
        _shotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, _numOfBounces);
        auto s = _shotPath.begin();
        _shot = new Projectile(s->x, s->y);
        _shot->setPath(_shotPath);
    }
    if(!_mouseIsAiming) {
        _collisionDetector.checkForClickableAction(_mouse.get(), _clickables);
        _collisionDetector.checkForClickableAction(_mouse.get(), _shop->getObjectBuyButtons());
    }
    for(auto bb : _shop->getObjectBuyButtons()) {
        auto oc = (ObjectClickable*) bb.get();
        if(oc->getObject() != nullptr) {
            _currentObjSelection = oc->getObject();
            _currentOC = oc;
            if(!_currentObjSelection->isInGrid()) {
                _currentObjSelection->setInGrid(true);
                _currentObjSelection->setObjectSpritesheet(getTileset());
            }
        }
    }

    if(_currentObjSelection) {
        // If object gets dropped
        if(!_mouse->isLeftButtonDown()) {
            // Using cool algorithm from https://stackoverflow.com/a/9194117
            _currentObjSelection->setPosition(
                (_currentObjSelection->getPosition().x - _grid->getTileSize() / 2 + _grid->getTileSize() - 1) & -_grid->getTileSize(),
                (_currentObjSelection->getPosition().y - _grid->getTileSize() / 2 + _grid->getTileSize() - 1) & -_grid->getTileSize());
            if(_tilemap->canPlaceObject(_currentObjSelection.get())) {
                _grid->addObject(_currentObjSelection);
                _currentObjSelection->setDrawShadows(true);
                for(auto edge : _currentObjSelection->getEdges()) {
                    _grid->addEdge(
                        {{_currentObjSelection->getPosition().x + edge.p1.x, _currentObjSelection->getPosition().y + edge.p1.y},
                        {_currentObjSelection->getPosition().x + edge.p2.x, _currentObjSelection->getPosition().y + edge.p2.y}});
                }
                _tilemap->setTile(_currentObjSelection->getPosition().x / _tilemap->getTileSize(),
                    _currentObjSelection->getPosition().y / _tilemap->getTileSize(),
                    _currentObjSelection->getTileType());
                _currentObjSelection->setMoveable(false);
            }
            else {
                _shop->setMoney(_shop->getMoney() + 1);
            }
            _currentObjSelection = nullptr;
            if(_currentOC) _currentOC->clearObject();
            _currentOC = nullptr;
            _guideLineShotPath = _collisionDetector.calculateShotPath(*_grid, _shotStart, _shotTarget, 0);
        }
        else {
            if(_pressingR && !_lastFramePressingR) {
                _currentOC->rotateRight();
                _currentObjSelection = _currentOC->getObject();
                _currentObjSelection->setInGrid(true);
                _currentObjSelection->setObjectSpritesheet(getTileset());
            }
            _currentObjSelection->setPosition(_mouse->getMouseX() - _grid->getTileSize() / 2,
                _mouse->getMouseY() - _grid->getTileSize() / 2);
        }
    }

    if(_nextLevelButton->hasBeenClicked()) {
        loadNextLevel();
    }

    _renderGrid = _shop->isOpen();
}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    // Render level
    const int tileSize = _tilemap->getTileSize();
    for(int x = 0; x < _tilemap->getTilemapWidth(); ++x) {
        for(int y = 0; y < _tilemap->getTilemapHeight(); ++y) {
            SDL_Rect tile = {x * tileSize + _renderOffset.x, y * tileSize + _renderOffset.y, tileSize, tileSize};
            switch(_tilemap->getTile(x, y)) {
                case TileType::EMPTY:
                case TileType::SQUARE:
                case TileType::RIGHT_TRIANGLE_NORTH:
                case TileType::RIGHT_TRIANGLE_EAST:
                case TileType::RIGHT_TRIANGLE_SOUTH:
                case TileType::RIGHT_TRIANGLE_WEST:
                case TileType::DIAMOND:
                case TileType::LONG_RIGHT_TRIANGLE_NORTH:
                case TileType::LONG_RIGHT_TRIANGLE_EAST:
                case TileType::LONG_RIGHT_TRIANGLE_SOUTH:
                case TileType::LONG_RIGHT_TRIANGLE_WEST:
                case TileType::GOAL_TILE:
                case TileType::START_TILE:
                    SDL_SetRenderDrawColor(getRenderer(), 0x64, 0x63, 0x65, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    if(_renderGrid) {
                        SDL_SetRenderDrawColor(getRenderer(), 0x21, 0x21, 0x23, 0xAF);
                        // Top
                        SDL_RenderDrawLine(getRenderer(), tile.x, tile.y, tile.x + tile.w, tile.y);
                        // Left
                        SDL_RenderDrawLine(getRenderer(), tile.x, tile.y, tile.x, tile.y + tile.h);
                        SDL_SetRenderDrawColor(getRenderer(), 0x35, 0x2b, 0x42, 0xAF);
                        // Right
                        SDL_RenderDrawLine(getRenderer(), tile.x + tile.w - 1, tile.y, tile.x + tile.w - 1, tile.y + tile.h - 1);
                        // Bottom
                        SDL_RenderDrawLine(getRenderer(), tile.x, tile.y + tile.h - 1, tile.x + tile.w - 1, tile.y + tile.h - 1);
                    }
                    break;
                default:
                    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0xFF, 0xFF);
                    SDL_RenderFillRect(getRenderer(), &tile);
                    break;
            }
            // DEBUG: draw all collision edges (hitboxes)
            if(_debug) {
                std::list<Edge> edges = _grid->getEdges(x, y);
                for(Edge e : edges) {
                    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0x00, 0xAF);
                    SDL_RenderDrawLine(getRenderer(), e.p1.x + _renderOffset.x, e.p1.y + _renderOffset.y, e.p2.x + _renderOffset.x, e.p2.y + _renderOffset.y);
                }
            }
        }
    }

    // Render objects
    if(!_debug) {
        for(auto obj : _grid->getObjects()) {
            if(obj.get() != _currentObjSelection.get()) obj->render(_renderOffset.x, _renderOffset.y);
        }
    }
    // Render entities
    for(auto ent : _grid->getEntities()) {
        ent->render(_renderOffset.x, _renderOffset.y);
    }

    // Render potential tile placement
    if(_currentObjSelection) {
        SDL_Rect rect = {
            ((_currentObjSelection->getPosition().x - _grid->getTileSize() / 2 + _grid->getTileSize() - 1) & -_grid->getTileSize()) + _renderOffset.x,
            ((_currentObjSelection->getPosition().y - _grid->getTileSize() / 2 + _grid->getTileSize() - 1) & -_grid->getTileSize()) + _renderOffset.y,
             _currentObjSelection->getNaturalSize().x,
             _currentObjSelection->getNaturalSize().y};
        if(_currentObjSelection->getTileType() == TileType::LONG_RIGHT_TRIANGLE_NORTH ||
            _currentObjSelection->getTileType() == TileType::LONG_RIGHT_TRIANGLE_SOUTH) {
            rect.w = _currentObjSelection->getNaturalSize().y;
            rect.h = _currentObjSelection->getNaturalSize().x;
        }
        if(_tilemap->canPlaceObject(_currentObjSelection->getTileType(), (rect.x + 16) / _grid->getTileSize(), (rect.y + 16) / _grid->getTileSize())) {
            SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0xFF, 0x90);
        }
        else {
            SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0x00, 0x90);
        }
        SDL_RenderFillRect(getRenderer(), &rect);
    }

    // Render shot path
    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0x00, 0x00, 0xAF);
    for(auto point : _guideLineShotPath) {
        SDL_RenderDrawPoint(getRenderer(), point.x + _renderOffset.x, point.y + _renderOffset.y);
    }

    // Render projectile
    if(_shot) {
        SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_Rect r = {_shot->getPosition().x + _renderOffset.x, _shot->getPosition().y + _renderOffset.y, 3, 3};
        SDL_RenderDrawRect(getRenderer(), &r);
    }

    // Render shop
    if(_shop->isOpen()) {
        _shop->render(getRenderer(), _renderOffset.x, _renderOffset.y);
        Text* smallText = getText(TextSize::SMALL);
        smallText->setPos(13, 14);
        smallText->setString(std::to_string(_shop->getMoney()));
        smallText->draw(_renderOffset.x, _renderOffset.y);
    }

    // Render clickables
    for(auto c : _clickables) {
        c->render(_renderOffset.x, _renderOffset.y);
    }

    // Render potential drag and drop objects
    if(_currentObjSelection) _currentObjSelection->render(_renderOffset.x, _renderOffset.y);

    // SDL_SetRenderDrawColor(getRenderer(), 0x00, 0xFF, 0xFF, 0x90);
    // SDL_Rect mouseRect = _mouse->getMouseGrabBox();
    // mouseRect.x += _renderOffset.x;
    // mouseRect.y += _renderOffset.y;
    // SDL_RenderFillRect(getRenderer(), &mouseRect);

    SDL_RenderPresent(getRenderer());
}

void GameState::loadNextLevel() {
    ++_currentLevelIndex;
    if(_currentLevelIndex >= _levels.size()) {
        std::cout << "Congratulations! You beat every level available." << std::endl;
        _currentLevelIndex = _levels.size() - 1;
    }
    std::vector<std::vector<int>> levelMap = LevelLoader::loadLevel(_levels[_currentLevelIndex]);
    _tilemap = std::make_unique<Tilemap>(getTileset(), levelMap);
    _defaultTilemap = levelMap;
    _grid = std::make_unique<Grid>(_tilemap->getGrid());
    _shotStart = _tilemap->getStart();
    _shotTarget = {_shotStart.x, 0};
    _shop->resetMoney();
    _nextLevelButton->setEnabled(false);
    _shop->setOpen(false);
}