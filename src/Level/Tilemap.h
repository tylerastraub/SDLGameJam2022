#ifndef TILEMAP_H
#define TILEMAP_H

#include "TileType.h"
#include "Grid.h"

#include <vector>
#include <memory>

class Tilemap {
public:
    Tilemap();
    Tilemap(int w, int h);
    // Constructor that allows tilemap to be generated based on vector of numbers. Useful for quickly creating
    // tilemaps for debugging purposes.
    Tilemap(std::vector<std::vector<int>> tilemap);
    ~Tilemap() = default;

    void allocateTilemap(int w, int h);
    void printTilemap();

    int getTilemapWidth();
    int getTilemapHeight();
    TileType getTile(int x, int y);
    int getTileSize();
    Grid getGrid();

private:
    const int TILE_SIZE = 32;

    int _tilemapWidth = 0;
    int _tilemapHeight = 0;

    std::vector<std::vector<TileType>> _tilemap;
    std::unique_ptr<Grid> _tilemapGrid = nullptr;
};

#endif