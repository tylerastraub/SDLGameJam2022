#include "RightTriangle.h"

#include <iostream>

RightTriangle::RightTriangle() {
    setTileType(TileType::RIGHT_TRIANGLE_NORTH);
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
            setTileType(TileType::RIGHT_TRIANGLE_NORTH);
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
            // Bottom
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, TILE_SIZE}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE}});
            break;
        case ObjectDirection::EAST:
            setTileType(TileType::RIGHT_TRIANGLE_EAST);
            // Hypotonuse
            addEdge({{0, TILE_SIZE}, {TILE_SIZE, 0}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE, 0}});
            // Left
            addEdge({{0, 0}, {0, TILE_SIZE}});
            break;
        case ObjectDirection::SOUTH:
            setTileType(TileType::RIGHT_TRIANGLE_SOUTH);
            // Hypotonuse
            addEdge({{0, 0}, {TILE_SIZE, TILE_SIZE}});
            // Top
            addEdge({{0, 0}, {TILE_SIZE, 0}});
            // Right
            addEdge({{TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE}});
            break;
        case ObjectDirection::WEST:
            setTileType(TileType::RIGHT_TRIANGLE_WEST);
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
    s->setTileWidth(getNaturalSize().x);
    s->setTileHeight(getNaturalSize().y);
    s->setRenderWidth(getRenderSize().x);
    s->setRenderHeight(getRenderSize().y);
    switch(getDirection()) {
        case(ObjectDirection::NORTH):
            if(drawShadows()) {
                s->setTileIndex(1, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2);
            }
            s->setTileIndex(1, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset);
            break;
        case(ObjectDirection::EAST):
            if(drawShadows()) {
                s->setTileIndex(1, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2, SDL_FLIP_NONE, 90.0);
            }
            s->setTileIndex(1, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 90.0);
            break;
        case(ObjectDirection::SOUTH):
            if(drawShadows()) {
                s->setTileIndex(1, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2, SDL_FLIP_NONE, 180.0);
            }
            s->setTileIndex(1, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 180.0);
            break;
        case(ObjectDirection::WEST):
            if(drawShadows()) {
                s->setTileIndex(1, 1);
                s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2, SDL_FLIP_NONE, 270.0);
            }
            s->setTileIndex(1, 0);
            s->render(getPosition().x + xOffset, getPosition().y + yOffset, SDL_FLIP_NONE, 270.0);
            break;
    }
}