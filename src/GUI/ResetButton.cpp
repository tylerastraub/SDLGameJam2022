#include "ResetButton.h"

ResetButton::ResetButton() {
    setClickRect({0, 0, 16, 16});
}

void ResetButton::onClick() {
    _requestReset = true;
}

void ResetButton::render(int xOffset, int yOffset) {
    // This should not be in a render loop but man's is pressed for time
    if(_shop->isOpen()) {
        setPosition(24 + _shop->getWidth(), 16);
    }
    else {
        setPosition(24, 16);
    }

    Spritesheet* s = getSpritesheet();
    s->setIsAnimated(false);
    s->setIsLooped(false);
    s->setRenderWidth(16);
    s->setRenderHeight(16);
    s->setTileWidth(16);
    s->setTileHeight(16);
    SDL_Point index = {5, 2}; 
    index.x = (isClicked()) ? 6 : 5;
    s->setTileIndex(index.x, index.y);
    s->render(getPosition().x + xOffset, getPosition().y + yOffset);
}

void ResetButton::setsRequestsReset(bool requestsReset) {
    _requestReset = requestsReset;
}

void ResetButton::setShop(Shop* shop) {
    _shop = shop;
}

bool ResetButton::requestsReset() {
    return _requestReset;
}