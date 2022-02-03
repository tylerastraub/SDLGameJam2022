#include "RightTriangle.h"

#include <iostream>

RightTriangle::RightTriangle() {
    // Hypotonuse
    addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
    // Bottom
    addEdge({{0, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE - 1}});
    // Left
    addEdge({{0, 0}, {0, 0}});
}

// TODO: fix gap between triangles (again)
RightTriangle::RightTriangle(ObjectDirection dir) {
    switch(dir) {
        case ObjectDirection::NORTH:
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
            // Bottom
            addEdge({{0, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE - 1}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE - 1}});
            break;
        case ObjectDirection::EAST:
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, 0}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE - 1, 0}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE - 1}});
            break;
        case ObjectDirection::SOUTH:
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE - 1, 0}});
            // Right
            addEdge({{TILE_SIZE - 1, 0}, {TILE_SIZE - 1, TILE_SIZE - 1}});
            break;
        case ObjectDirection::WEST:
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, 0}});
            // Bottom
            addEdge({{0, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE - 1}});
            // Right
            addEdge({{TILE_SIZE - 1, 0}, {TILE_SIZE - 1, TILE_SIZE - 1}});
            break;
        default:
            // Invalid direction, no edges set
            break;
    }
}