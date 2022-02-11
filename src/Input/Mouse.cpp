#include "Mouse.h"

Mouse::Mouse(float xRenderScale, float yRenderScale) : _xRenderScale(xRenderScale), _yRenderScale(yRenderScale) {
    _mouseGrabBox.w = 8;
    _mouseGrabBox.h = 8;
}

void Mouse::setPos(int x, int y) {
    _mousePos = {x / (int) _xRenderScale, y / (int) _yRenderScale};
    _mouseGrabBox.x = _mousePos.x - _mouseGrabBox.w / 2;
    _mouseGrabBox.y = _mousePos.y - _mouseGrabBox.h / 2;
}

void Mouse::setLeftButtonDown(bool leftButtonDown) {
    _leftButtonDown = leftButtonDown;
}

void Mouse::setRightButtonDown(bool rightButtonDown) {
    _rightButtonDown = rightButtonDown;
}

void Mouse::setMouseMoved(bool moved) {
    _mouseMoved = moved;
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

SDL_Rect Mouse::getMouseGrabBox() {
    return _mouseGrabBox;
}

bool Mouse::isLeftButtonDown() {
    return _leftButtonDown;
}

bool Mouse::isRightButtonDown() {
    return _rightButtonDown;
}

bool Mouse::mouseMoved() {
    return _mouseMoved;
}