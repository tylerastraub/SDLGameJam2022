#include "Diamond.h"

Diamond::Diamond() {
    // Top left
    addEdge({{0, TILE_SIZE / 2 - 1}, {TILE_SIZE / 2 - 1, 0}});
    // Top right
    addEdge({{TILE_SIZE / 2, 0}, {TILE_SIZE - 1, TILE_SIZE / 2 - 1}});
    // bottom left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2 - 1, TILE_SIZE - 1}});
    // bottom right
    addEdge({{TILE_SIZE / 2, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE / 2}});
}

Diamond::Diamond(ObjectDirection dir) {
    // Top left
    addEdge({{0, TILE_SIZE / 2 - 1}, {TILE_SIZE / 2 - 1, 0}});
    // Top right
    addEdge({{TILE_SIZE / 2, 0}, {TILE_SIZE - 1, TILE_SIZE / 2 - 1}});
    // bottom left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2 - 1, TILE_SIZE - 1}});
    // bottom right
    addEdge({{TILE_SIZE / 2, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE / 2}});
}