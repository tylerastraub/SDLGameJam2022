#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "Spritesheet.h"

#include <SDL.h>

class Clickable {
public:
    Clickable() = default;
    ~Clickable() = default;

    virtual void onLeftMouseButtonDown() = 0;
    virtual void onLeftMouseButtonUp() = 0;
    virtual void render(int xOffset, int yOffset) = 0;

    void setClickRect(SDL_Rect rect);
    void setPosition(int x, int y);
    void setClicked(bool clicked);
    void setSpritesheet(Spritesheet* spritesheet);

    SDL_Rect getClickRect();
    SDL_Point getPosition();
    bool isClicked();
    Spritesheet* getSpritesheet();

private:
    SDL_Rect _clickRect = {0, 0, 0, 0};
    SDL_Point _position = {0, 0};

    bool _clicked = false;

    Spritesheet* _clickableSpritesheet = nullptr;

};

#endif