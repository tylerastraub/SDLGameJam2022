#include "Square.h"

Square::Square() {
    // Top
    addEdge({{-1, -1}, {TILE_SIZE, -1}});
    // Right
    addEdge({{TILE_SIZE, -1}, {TILE_SIZE, TILE_SIZE}});
    // Bottom
    addEdge({{-1, TILE_SIZE}, {TILE_SIZE, TILE_SIZE}});
    // Left
    addEdge({{-1, -1}, {-1, TILE_SIZE}});
}

Square::Square(ObjectDirection dir) {
    // Top
    addEdge({{-1, -1}, {TILE_SIZE, -1}});
    // Right
    addEdge({{TILE_SIZE, -1}, {TILE_SIZE, TILE_SIZE}});
    // Bottom
    addEdge({{-1, TILE_SIZE}, {TILE_SIZE, TILE_SIZE}});
    // Left
    addEdge({{-1, -1}, {-1, TILE_SIZE}});
}