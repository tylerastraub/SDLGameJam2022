#include "NextLevelButton.h"

void NextLevelButton::onClick() {
    _hasBeenClicked = true;
}

void NextLevelButton::render(int xOffset, int yOffset) {
    // Still pressed for time please don't hate
    if(_shop->isOpen()) {
        setPosition(44 + _shop->getWidth(), 16);
    }
    else {
        setPosition(44, 16);
    }
    
    if(_isEnabled) {
        Spritesheet* s = getSpritesheet();
        s->setIsAnimated(false);
        s->setIsLooped(false);
        s->setRenderWidth(32);
        s->setRenderHeight(16);
        s->setTileWidth(32);
        s->setTileHeight(16);
        SDL_Point index = {3, 2}; 
        index.x = (isClicked()) ? 4 : 3;
        s->setTileIndex(index.x, index.y);
        s->render(getPosition().x + xOffset, getPosition().y + yOffset);
    }
}

void NextLevelButton::setEnabled(bool enabled) {
    _isEnabled = enabled;
    if(_isEnabled) {
        setClickRect({getPosition().x, getPosition().y, 32, 16});
    }
    else {
        _hasBeenClicked = false;
    }
}

void NextLevelButton::setShop(Shop* shop) {
    _shop = shop;
}

bool NextLevelButton::isEnabled() {
    return _isEnabled;
}

bool NextLevelButton::hasBeenClicked() {
    return _hasBeenClicked;
}