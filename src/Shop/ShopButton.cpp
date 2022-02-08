#include "ShopButton.h"

#include <iostream>

ShopButton::ShopButton() {
    setClickRect({0, 0, 16, 16});
}

void ShopButton::onClick() {
    std::cout << "Shop button clicked!" << std::endl;
}

void ShopButton::render(int xOffset, int yOffset) {
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(16);
    s->setTileHeight(16);
    SDL_Point index = {10, 2}; 
    index.x = (isClicked()) ? 12 : 10;
    s->setTileIndex(index.x, index.y);
    s->render(getPosition().x + xOffset, getPosition().y + yOffset);
}

void ShopButton::setShop(Shop* shop) {
    _shop = shop;
}

Shop* ShopButton::getShop() {
    return _shop;
}