#include "Mouse.h"

Mouse::Mouse(float xRenderScale, float yRenderScale)
    : _xRenderScale(xRenderScale), _yRenderScale(yRenderScale) {}

void Mouse::setPos(int x, int y) {
    _mousePos = {x / (int) _xRenderScale, y / (int) _yRenderScale};
}

void Mouse::setLeftButtonDown(bool leftButtonDown) {
    _leftButtonDown = leftButtonDown;
}

void Mouse::setRightButtonDown(bool rightButtonDown) {
    _rightButtonDown = rightButtonDown;
}

SDL_Point Mouse::getMousePos() {
    return _mousePos;
}

int Mouse::getMouseX() {
    return _mousePos.x;
}

int Mouse::getMouseY() {
    return _mousePos.y;
}

bool Mouse::isLeftButtonDown() {
    return _leftButtonDown;
}

bool Mouse::isRightButtonDown() {
    return _rightButtonDown;
}