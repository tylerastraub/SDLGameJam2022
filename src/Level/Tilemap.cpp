#include "Tilemap.h"

#include <iostream>

Tilemap::Tilemap(int w, int h) {
    allocateTilemap(w, h);
}

Tilemap::Tilemap(std::vector<std::vector<int>> tilemap) {
    _tilemapHeight = tilemap.size();
    _tilemapWidth = tilemap[0].size();
    std::cout << _tilemapWidth << ", " << _tilemapHeight << std::endl;
    for(int y = 0; y < _tilemapHeight; ++y) {
        std::vector<TileType> row;
        for(int x = 0; x < _tilemapWidth; ++x) {
            row.push_back((TileType) tilemap[y][x]);
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
}

void Tilemap::printTilemap() {
    for(int y = 0; y < _tilemapHeight; ++y) {
        for(int x = 0; x < _tilemapWidth; ++x) {
            std::cout << _tilemap[y][x] << "\t";
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