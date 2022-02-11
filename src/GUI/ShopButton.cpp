#include "ShopButton.h"

#include <iostream>

ShopButton::ShopButton() {
    setClickRect({0, 0, 16, 16});
}

void ShopButton::onClick() {
    if(_shop->isOpen()) {
        _shop->setOpen(false);
        setPosition(getPosition().x - _shop->getWidth(), getPosition().y);
    }
    else {
        _shop->setOpen(true);
        setPosition(getPosition().x + _shop->getWidth(), getPosition().y);
    }
}

void ShopButton::render(int xOffset, int yOffset) {
    if(!_shop->isOpen()) {
        setPosition(4, getPosition().y);
    }
    else {
        setPosition(4 + _shop->getWidth(), getPosition().y);
    }
    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setTileWidth(16);
    s->setTileHeight(16);
    s->setRenderWidth(16);
    s->setRenderHeight(16);
    SDL_Point index = {5, 1}; 
    index.x = (isClicked()) ? 6 : 5;
    s->setTileIndex(index.x, index.y);
    s->render(getPosition().x + xOffset, getPosition().y + yOffset);
}

void ShopButton::setShop(Shop* shop) {
    _shop = shop;
}

Shop* ShopButton::getShop() {
    return _shop;
}