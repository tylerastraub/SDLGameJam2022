#include "Clickable.h"

void Clickable::setClickRect(SDL_Rect rect) {
    _clickRect = rect;
}

void Clickable::setPosition(int x, int y) {
    _position = {x, y};
    _clickRect.x = x;
    _clickRect.y = y;
}

void Clickable::setClicked(bool clicked) {
    _clicked = clicked;
}

void Clickable::setSpritesheet(Spritesheet* spritesheet) {
    _clickableSpritesheet = spritesheet;
}

SDL_Rect Clickable::getClickRect() {
    return _clickRect;
}

SDL_Point Clickable::getPosition() {
    return _position;
}

bool Clickable::isClicked() {
    return _clicked;
}

Spritesheet* Clickable::getSpritesheet() {
    return _clickableSpritesheet;
}