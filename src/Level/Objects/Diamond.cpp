#include "Diamond.h"

// Note that left corner of diamond has some funky collisions properties... need to fix at some point
Diamond::Diamond() {
    // Top left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, 0}});
    // Top right
    addEdge({{TILE_SIZE / 2, 0}, {TILE_SIZE - 1, TILE_SIZE / 2}});
    // bottom left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, TILE_SIZE - 1}});
    // bottom right
    addEdge({{TILE_SIZE / 2, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE / 2}});
}

Diamond::Diamond(ObjectDirection dir) {
    // Top left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, 0}});
    // Top right
    addEdge({{TILE_SIZE / 2, 0}, {TILE_SIZE - 1, TILE_SIZE / 2}});
    // bottom left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, TILE_SIZE - 1}});
    // bottom right
    addEdge({{TILE_SIZE / 2, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE / 2}});
}