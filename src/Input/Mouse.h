#ifndef MOUSE_H
#define MOUSE_H

#include <SDL.h>

class Mouse {
public:
    Mouse() = default;
    ~Mouse() = default;

    void setPos(int x, int y);
    void setLeftButtonDown(bool leftButtonDown);
    void setRightButtonDown(bool rightButtonDown);

private:
    SDL_Point _mousePos = {0, 0};
    bool _leftButtonDown = false;
    bool _rightButtonDown = false;
};

#endif