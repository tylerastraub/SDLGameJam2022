#include "Tilemap.h"
#include "RightTriangle.h"
#include "Square.h"
#include "Diamond.h"
#include "LongRightTriangle.h"
#include "Goal.h"

#include <iostream>

Tilemap::Tilemap() {
    _tilemapGrid = std::make_unique<Grid>(TILE_SIZE);
}

Tilemap::Tilemap(int w, int h) {
    allocateTilemap(w, h);
}

Tilemap::Tilemap(Spritesheet* tileset, std::vector<std::vector<int>> tilemap) {
    _tilemapHeight = tilemap.size();
    _tilemapWidth = tilemap[0].size();
    _tilemapGrid = std::make_unique<Grid>(TILE_SIZE, _tilemapWidth, _tilemapHeight);
    _tilemapGrid->setTileset(tileset);
    for(int y = 0; y < _tilemapHeight; ++y) {
        std::vector<TileType> row;
        for(int x = 0; x < _tilemapWidth; ++x) {
            row.push_back((TileType) tilemap[y][x]);
            switch(tilemap[y][x]) {
                case(TileType::SQUARE): {
                    std::shared_ptr<Square> square = std::make_shared<Square>();
                    square->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(square);
                    for(auto edge : square->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_NORTH): {
                    std::shared_ptr<RightTriangle> triangle = std::make_shared<RightTriangle>(ObjectDirection::NORTH);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_EAST): {
                    std::shared_ptr<RightTriangle> triangle = std::make_shared<RightTriangle>(ObjectDirection::EAST);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_SOUTH): {
                    std::shared_ptr<RightTriangle> triangle = std::make_shared<RightTriangle>(ObjectDirection::SOUTH);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_WEST): {
                    std::shared_ptr<RightTriangle> triangle = std::make_shared<RightTriangle>(ObjectDirection::WEST);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::DIAMOND): {
                    std::shared_ptr<Diamond> diamond = std::make_shared<Diamond>();
                    diamond->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(diamond);
                    for(auto edge : diamond->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::LONG_RIGHT_TRIANGLE_NORTH): {
                    std::shared_ptr<LongRightTriangle> triangle = std::make_shared<LongRightTriangle>(ObjectDirection::NORTH);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::LONG_RIGHT_TRIANGLE_EAST): {
                    std::shared_ptr<LongRightTriangle> triangle = std::make_shared<LongRightTriangle>(ObjectDirection::EAST);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::LONG_RIGHT_TRIANGLE_SOUTH): {
                    std::shared_ptr<LongRightTriangle> triangle = std::make_shared<LongRightTriangle>(ObjectDirection::SOUTH);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::LONG_RIGHT_TRIANGLE_WEST): {
                    std::shared_ptr<LongRightTriangle> triangle = std::make_shared<LongRightTriangle>(ObjectDirection::WEST);
                    triangle->setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addObject(triangle);
                    for(auto edge : triangle->getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::GOAL_TILE): {
                    std::shared_ptr<Goal> goal = std::make_shared<Goal>(x * TILE_SIZE, y * TILE_SIZE);
                    _tilemapGrid->addEntity(goal);
                    break;
                }
            }
        }
        _tilemap.push_back(row);
    }
}

void Tilemap::allocateTilemap(int w, int h) {
    _tilemapWidth = w;
    _tilemapHeight = h;
    for(int y = 0; y < h; ++y) {
        std::vector<TileType> row;
        for(int x = 0; x < w; ++x) {
            row.push_back(TileType::EMPTY);
        }
        _tilemap.push_back(row);
    }
    _tilemapGrid = std::make_unique<Grid>(TILE_SIZE, _tilemapWidth, _tilemapHeight);
}

void Tilemap::printTilemap() {
    for(int y = 0; y < _tilemapHeight; ++y) {
        for(int x = 0; x < _tilemapWidth; ++x) {
            std::cout << _tilemap[y][x] << "  ";
        }
        std::cout << std::endl;
    }
}

bool Tilemap::canPlaceObject(Object* obj) {
    SDL_Point objectTilePos = {obj->getPosition().x / TILE_SIZE, obj->getPosition().y / TILE_SIZE};
    switch(obj->getTileType()) {
        case(TileType::SQUARE):
        case(TileType::DIAMOND):
        case(TileType::RIGHT_TRIANGLE_NORTH):
        case(TileType::RIGHT_TRIANGLE_EAST):
        case(TileType::RIGHT_TRIANGLE_SOUTH):
        case(TileType::RIGHT_TRIANGLE_WEST):
            return (getTile(objectTilePos.x, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_NORTH):
            return (getTile(objectTilePos.x, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(objectTilePos.x, objectTilePos.y + 1) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y + 1) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y + 1) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_EAST):
            return (getTile(objectTilePos.x, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(objectTilePos.x + 1, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x + 1, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x + 1, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_SOUTH):
            return (getTile(objectTilePos.x, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(objectTilePos.x, objectTilePos.y + 1) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y + 1) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y + 1) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_WEST):
            return (getTile(objectTilePos.x, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x - 1, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(objectTilePos.x + 1, objectTilePos.y) == TileType::EMPTY &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(objectTilePos.x, objectTilePos.y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(objectTilePos.x + 1, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(objectTilePos.x + 1, objectTilePos.y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
    }

    return false;
}

bool Tilemap::canPlaceObject(TileType tileType, int x, int y) {
    switch(tileType) {
        case(TileType::SQUARE):
        case(TileType::DIAMOND):
        case(TileType::RIGHT_TRIANGLE_NORTH):
        case(TileType::RIGHT_TRIANGLE_EAST):
        case(TileType::RIGHT_TRIANGLE_SOUTH):
        case(TileType::RIGHT_TRIANGLE_WEST):
            return (getTile(x, y) == TileType::EMPTY &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_NORTH):
            return (getTile(x, y) == TileType::EMPTY &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(x, y + 1) == TileType::EMPTY &&
                getTile(x - 1, y + 1) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y + 1) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_EAST):
            return (getTile(x, y) == TileType::EMPTY &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(x + 1, y) == TileType::EMPTY &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x + 1, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x + 1, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_SOUTH):
            return (getTile(x, y) == TileType::EMPTY &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(x, y + 1) == TileType::EMPTY &&
                getTile(x - 1, y + 1) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y + 1) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
        case(TileType::LONG_RIGHT_TRIANGLE_WEST):
            return (getTile(x, y) == TileType::EMPTY &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x - 1, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH &&
                getTile(x + 1, y) == TileType::EMPTY &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_EAST &&
                getTile(x, y) != TileType::LONG_RIGHT_TRIANGLE_WEST &&
                getTile(x + 1, y - 1) != TileType::LONG_RIGHT_TRIANGLE_NORTH &&
                getTile(x + 1, y - 1) != TileType::LONG_RIGHT_TRIANGLE_SOUTH);
            break;
    }

    return false;
}

void Tilemap::setTile(int x, int y, TileType tileType) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        _tilemap[y][x] = tileType;
    }
}

int Tilemap::getTilemapWidth() {
    return _tilemapWidth;
}

int Tilemap::getTilemapHeight() {
    return _tilemapHeight;
}

TileType Tilemap::getTile(int x, int y) {
    if(x >= 0 && x < _tilemapWidth && y >= 0 && y < _tilemapHeight) {
        return _tilemap[y][x];
    }
    return TileType::SQUARE;
}

int Tilemap::getTileSize() {
    return TILE_SIZE;
}

Grid Tilemap::getGrid() {
    return *_tilemapGrid.get();
}