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
    setDirection(dir);
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

void LongRightTriangle::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(64);
    s->setTileHeight(32);
    s->setTileIndex(1, 0);
    switch(getDirection()) {
        case(ObjectDirection::NORTH):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 270.0, {32, 32});
            break;
        case(ObjectDirection::EAST):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE);
            break;
        case(ObjectDirection::SOUTH):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 90.0, {16, 16});
            break;
        case(ObjectDirection::WEST):
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 180.0, {32, 16});
            break;
    }
}