#include "LongRightTriangle.h"

LongRightTriangle::LongRightTriangle() {
    // Hypotonuse
    addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE * 2}});
    // Left
    addEdge({{0, 0}, {0, TILE_SIZE * 2}});
    // Bottom
    addEdge({{0, TILE_SIZE * 2}, {TILE_SIZE, TILE_SIZE * 2}});
}

LongRightTriangle::LongRightTriangle(ObjectDirection dir) {
    switch(dir) {
        case(ObjectDirection::NORTH):
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE * 2}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE * 2}});
            // Bottom
            addEdge({{0, TILE_SIZE * 2}, {TILE_SIZE, TILE_SIZE * 2}});
            break;
        case(ObjectDirection::EAST):
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE * 2, 0}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE * 2, 0}});
            break;
        case(ObjectDirection::SOUTH):
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE * 2}});
            // Right
            addEdge({{TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE * 2}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE, 0}});
            break;
        case(ObjectDirection::WEST):
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE * 2, 0}});
            // Right
            addEdge({{TILE_SIZE * 2, 0}, {TILE_SIZE * 2, TILE_SIZE}});
            // Bottom
            addEdge({{0, TILE_SIZE}, {TILE_SIZE * 2, TILE_SIZE}});
            break;
    }
}