#include "RightTriangle.h"

#include <iostream>

RightTriangle::RightTriangle() {
    // Hypotonuse
    addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
    // Bottom
    addEdge({{0, TILE_SIZE}, {TILE_SIZE, TILE_SIZE}});
    // Left
    addEdge({{0, 0}, {0, 0}});
}

// TODO: fix gap between triangles (again)
RightTriangle::RightTriangle(ObjectDirection dir) {
    setDirection(dir);
    switch(dir) {
        case ObjectDirection::NORTH:
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
            // Bottom
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, TILE_SIZE}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE}});
            break;
        case ObjectDirection::EAST:
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, 0}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE, 0}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE}});
            break;
        case ObjectDirection::SOUTH:
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE, 0}});
            // Right
            addEdge({{TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE}});
            break;
        case ObjectDirection::WEST:
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, 0}});
            // Bottom
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, TILE_SIZE}});
            // Right
            addEdge({{TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE}});
            break;
        default:
            // Invalid direction, no edges set
            break;
    }
}

void RightTriangle::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(32);
    s->setTileHeight(32);
    s->setTileIndex(1, 0);
    switch(getDirection()) {
        case(ObjectDirection::NORTH):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset);
            break;
        case(ObjectDirection::EAST):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 90.0);
            break;
        case(ObjectDirection::SOUTH):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 180.0);
            break;
        case(ObjectDirection::WEST):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 270.0);
            break;
    }
}