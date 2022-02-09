#include "Shop.h"
#include "Square.h"
#include "RightTriangle.h"
#include "Diamond.h"
#include "LongRightTriangle.h"

Shop::Shop() {
    _inventory.push_back(std::make_shared<Square>(ObjectDirection::NORTH));
    _inventory[0]->setRenderSize(16, 16);
    _inventory[0]->setDrawShadows(false);
    _inventory.push_back(std::make_shared<RightTriangle>(ObjectDirection::NORTH));
    _inventory[1]->setRenderSize(16, 16);
    _inventory[1]->setDrawShadows(false);
    _inventory.push_back(std::make_shared<LongRightTriangle>(ObjectDirection::NORTH));
    _inventory[2]->setRenderSize(8, 16);
    _inventory[2]->setDrawShadows(false);
    _inventory.push_back(std::make_shared<Diamond>(ObjectDirection::NORTH));
    _inventory[3]->setRenderSize(16, 16);
    _inventory[3]->setDrawShadows(false);
}

void Shop::render(SDL_Renderer* renderer, int xOffset, int yOffset) {
    _shopSpritesheet->setIsAnimated(false);
    _shopSpritesheet->setIsLooped(false);
    SDL_Rect topRect = {0, 0, 32, 16 + (int) _inventory.size() * 28};
    SDL_SetRenderDrawColor(renderer, 0x4e, 0x58, 0x4a, 0xFF);
    SDL_RenderFillRect(renderer, &topRect);
    SDL_SetRenderDrawColor(renderer, 0x21, 0x21, 0x23, 0xFF);
    SDL_RenderDrawRect(renderer, &topRect);
    // Render coin
    _shopSpritesheet->setTileIndex(7, 2);
    _shopSpritesheet->setTileWidth(6);
    _shopSpritesheet->setTileHeight(8);
    _shopSpritesheet->setRenderWidth(6);
    _shopSpritesheet->setRenderHeight(8);
    _shopSpritesheet->render(_position.x + xOffset + 4, _position.y + yOffset + 4);
    for(int y = 0; y < _inventory.size(); ++y) {
        // Render tile
        _shopSpritesheet->setTileIndex(7, 1);
        _shopSpritesheet->setTileWidth(24);
        _shopSpritesheet->setTileHeight(24);
        _shopSpritesheet->setRenderWidth(24);
        _shopSpritesheet->setRenderHeight(24);
        _shopSpritesheet->render(_position.x + xOffset + 4, _position.y + y * 28 + yOffset + 16);
        // Render object
        Object* obj = _inventory[y].get();
        int yIndex = (obj->getNaturalSize().x > 32) ? 2 : 28;
        obj->render(_position.x + xOffset + 8, _position.y + y * yIndex + yOffset + 20);
    }
}

void Shop::setOpen(bool open) {
    _opened = open;
    if(_opened) {
        _size.x = _maxSize.x;
        _size.y = _maxSize.y;
    }
    else {
        _size = {0, 0};
    }
}

void Shop::setSpritesheet(Spritesheet* spritesheet) {
    _shopSpritesheet = spritesheet;
    for(auto obj : _inventory) {
        obj->setObjectSpritesheet(spritesheet);
    }
}

bool Shop::isOpen() {
    return _opened;
}

int Shop::getWidth() {
    return _maxSize.x;
}

int Shop::getHeight() {
    return _maxSize.y;
}