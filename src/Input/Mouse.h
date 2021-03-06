#ifndef MOUSE_H
#define MOUSE_H

#include <SDL.h>

class Mouse {
public:
    /** 
     * Creates a wrapper class that contains mouse info from SDL_GetMouseState(). This should be
     * handled in the state that creates the mouse.
     * 
     * @param renderScale The ratio between the logical game size and the actual screen width. SDL_GetMouseState()
     * returns coordinates of the mouse relative to actual screen size, so to get anything useful
     * to the actual game, coordinates need to be scaled appropriately.
     * 
     **/
    Mouse(float xRenderScale, float yRenderScale);
    ~Mouse() = default;

    void setPos(int x, int y);
    void setLeftButtonDown(bool leftButtonDown);
    void setRightButtonDown(bool rightButtonDown);
    void setMouseMoved(bool moved);

    SDL_Point getMousePos();
    int getMouseX();
    int getMouseY();
    int getMouseDX();
    int getMouseDY();
    SDL_Rect getMouseGrabBox();
    bool isLeftButtonDown();
    bool isRightButtonDown();
    bool mouseMoved();

private:
    SDL_Point _mousePos = {0, 0};
    SDL_Point _mouseDelta = {0, 0};
    SDL_Rect _mouseGrabBox = {0, 0, 0, 0};
    bool _leftButtonDown = false;
    bool _rightButtonDown = false;
    bool _mouseMoved = false;

    float _xRenderScale = 0.f;
    float _yRenderScale = 0.f;;
};

#endif