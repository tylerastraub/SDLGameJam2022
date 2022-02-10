#include "Diamond.h"

// Note that left corner of diamond has some funky collisions properties... need to fix at some point
Diamond::Diamond() {
    setTileType(TileType::DIAMOND);
    // Top left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, 0}});
    // Top right
    addEdge({{TILE_SIZE / 2, 0}, {TILE_SIZE, TILE_SIZE / 2}});
    // bottom left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, TILE_SIZE}});
    // bottom right
    addEdge({{TILE_SIZE / 2, TILE_SIZE}, {TILE_SIZE, TILE_SIZE / 2}});
}

Diamond::Diamond(ObjectDirection dir) {
    setTileType(TileType::DIAMOND);
    // Top left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, 0}});
    // Top right
    addEdge({{TILE_SIZE / 2, 0}, {TILE_SIZE - 1, TILE_SIZE / 2}});
    // bottom left
    addEdge({{0, TILE_SIZE / 2}, {TILE_SIZE / 2, TILE_SIZE - 1}});
    // bottom right
    addEdge({{TILE_SIZE / 2, TILE_SIZE - 1}, {TILE_SIZE - 1, TILE_SIZE / 2}});
}

void Diamond::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(getNaturalSize().x);
    s->setTileHeight(getNaturalSize().y);
    s->setRenderWidth(getRenderSize().x);
    s->setRenderHeight(getRenderSize().y);
    if(drawShadows()) {
        s->setTileIndex(4, 1);
        s->render(getPosition().x + xOffset + 2, getPosition().y + yOffset + 2);
    }
    s->setTileIndex(4, 0);
    s->render(getPosition().x + xOffset, getPosition().y + yOffset);
}