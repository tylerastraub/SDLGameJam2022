#include "Mouse.h"

void Mouse::setPos(int x, int y) {
    _mousePos = {x, y};
}

void Mouse::setLeftButtonDown(bool leftButtonDown) {
    _leftButtonDown = leftButtonDown;
}

void Mouse::setRightButtonDown(bool rightButtonDown) {
    _rightButtonDown = rightButtonDown;
}