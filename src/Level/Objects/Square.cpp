#include "Square.h"

#include <iostream>

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

void Square::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(32);
    s->setTileHeight(32);
    if(drawShadows()) {
        s->setTileIndex(0, 1);
        s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2);
    }
    s->setTileIndex(0, 0);
    s->render(getPosition().x + xOffset, getPosition().y + yOffset);
}