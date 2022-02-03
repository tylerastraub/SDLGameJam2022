#include "Square.h"

Square::Square() {
    // Top
    addEdge({{0, 0}, {TILE_SIZE - 1, 0}});
    // Right
    addEdge({{TILE_SIZE - 1, 0}, {TILE_SIZE - 1, TILE_SIZE - 1}});
    // Bottom
    addEdge({{0, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE - 1}});
    // Left
    addEdge({{0, 0}, {0, TILE_SIZE - 1}});
}

Square::Square(ObjectDirection dir) {
    // Top
    addEdge({{0, 0}, {TILE_SIZE - 1, 0}});
    // Right
    addEdge({{TILE_SIZE - 1, 0}, {TILE_SIZE - 1, TILE_SIZE - 1}});
    // Bottom
    addEdge({{0, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE - 1}});
    // Left
    addEdge({{0, 0}, {0, TILE_SIZE - 1}});
}