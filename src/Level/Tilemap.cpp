#include "Tilemap.h"

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
            if(tilemap[y][x] == TileType::SOLID) {
                // Top
                _tilemapGrid->addEdge({{x * TILE_SIZE, y * TILE_SIZE}, {(x + 1) * TILE_SIZE - 1, y * TILE_SIZE}});
                // Bottom
                _tilemapGrid->addEdge({{x * TILE_SIZE, (y + 1) * TILE_SIZE - 1}, {(x + 1) * TILE_SIZE - 1, (y + 1) * TILE_SIZE - 1}});
                // Left
                _tilemapGrid->addEdge({{x * TILE_SIZE, y * TILE_SIZE}, {x * TILE_SIZE, (y + 1) * TILE_SIZE - 1}});
                // Right
                _tilemapGrid->addEdge({{(x + 1) * TILE_SIZE - 1, y * TILE_SIZE}, {(x + 1) * TILE_SIZE - 1, (y + 1) * TILE_SIZE - 1}});
            }
            else if(tilemap[y][x] == TileType::SPECIAL) {
                // Hypotonuse
                _tilemapGrid->addEdge({{x * TILE_SIZE, y * TILE_SIZE}, {(x + 1) * TILE_SIZE - 1, (y + 1) * TILE_SIZE - 1}});
                // Bottom
                _tilemapGrid->addEdge({{x * TILE_SIZE, (y + 1) * TILE_SIZE - 1}, {(x + 1) * TILE_SIZE - 1, (y + 1) * TILE_SIZE - 1}});
                // Left
                _tilemapGrid->addEdge({{x * TILE_SIZE, y * TILE_SIZE}, {x * TILE_SIZE, (y + 1) * TILE_SIZE - 1}});
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