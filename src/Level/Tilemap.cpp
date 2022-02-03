#include "Tilemap.h"
#include "RightTriangle.h"
#include "Square.h"

#include <iostream>

Tilemap::Tilemap() {
    _tilemapGrid = std::make_unique<Grid>(TILE_SIZE);
}

Tilemap::Tilemap(int w, int h) {
    allocateTilemap(w, h);
}

Tilemap::Tilemap(std::vector<std::vector<int>> tilemap) {
    _tilemapHeight = tilemap.size();
    _tilemapWidth = tilemap[0].size();
    _tilemapGrid = std::make_unique<Grid>(TILE_SIZE, _tilemapWidth, _tilemapHeight);
    for(int y = 0; y < _tilemapHeight; ++y) {
        std::vector<TileType> row;
        for(int x = 0; x < _tilemapWidth; ++x) {
            row.push_back((TileType) tilemap[y][x]);
            switch(tilemap[y][x]) {
                case(TileType::SQUARE): {
                    Square square;
                    for(auto edge : square.getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_NORTH): {
                    RightTriangle triangle(ObjectDirection::NORTH);
                    for(auto edge : triangle.getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_EAST): {
                    RightTriangle triangle(ObjectDirection::EAST);
                    for(auto edge : triangle.getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_SOUTH): {
                    RightTriangle triangle(ObjectDirection::SOUTH);
                    for(auto edge : triangle.getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
                    break;
                }
                case(TileType::RIGHT_TRIANGLE_WEST): {
                    RightTriangle triangle(ObjectDirection::WEST);
                    for(auto edge : triangle.getEdges()) {
                        _tilemapGrid->addEdge({{x * TILE_SIZE + edge.p1.x, y * TILE_SIZE + edge.p1.y},
                            {x * TILE_SIZE + edge.p2.x, y * TILE_SIZE + edge.p2.y}});
                    }
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

int Tilemap::getTilemapWidth() {
    return _tilemapWidth;
}

int Tilemap::getTilemapHeight() {
    return _tilemapHeight;
}

TileType Tilemap::getTile(int x, int y) {
    return _tilemap[y][x];
}

int Tilemap::getTileSize() {
    return TILE_SIZE;
}

Grid Tilemap::getGrid() {
    return *_tilemapGrid.get();
}