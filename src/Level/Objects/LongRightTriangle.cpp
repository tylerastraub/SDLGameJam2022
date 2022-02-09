#include "LongRightTriangle.h"

LongRightTriangle::LongRightTriangle() {
    // Hypotonuse
    addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE * 2}});
    // Left
    addEdge({{0, 0}, {0, TILE_SIZE * 2}});
    // Bottom
    addEdge({{0, TILE_SIZE * 2}, {TILE_SIZE, TILE_SIZE * 2}});
    setRenderSize(64, 32);
    setNaturalSize(64, 32);
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
    setRenderSize(64, 32);
    setNaturalSize(64, 32);
}

void LongRightTriangle::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(getNaturalSize().x);
    s->setTileHeight(getNaturalSize().y);
    s->setRenderWidth(getRenderSize().x);
    s->setRenderHeight(getRenderSize().y);
    switch(getDirection()) {
        case(ObjectDirection::NORTH):
            if(drawShadows()) {
                s->setTileIndex(2, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2, SDL_FLIP_NONE, 270.0, {32, 32});
            }
            s->setTileIndex(2, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 270.0, {32, 32});
            break;
        case(ObjectDirection::EAST):
            if(drawShadows()) {
                s->setTileIndex(2, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2);
            }
            s->setTileIndex(2, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset);
            break;
        case(ObjectDirection::SOUTH):
            if(drawShadows()) {
                s->setTileIndex(2, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2, SDL_FLIP_NONE, 90.0, {16, 16});
            }
            s->setTileIndex(2, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 90.0, {16, 16});
            break;
        case(ObjectDirection::WEST):
            if(drawShadows()) {
                s->setTileIndex(2, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2, SDL_FLIP_NONE, 180.0, {32, 16});
            }
            s->setTileIndex(2, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 180.0, {32, 16});
            break;
    }
}