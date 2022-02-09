#ifndef SHOP_H
#define SHOP_H

#include "Spritesheet.h"
#include "Object.h"

#include <vector>
#include <memory>

class Shop {
public:
    Shop();
    ~Shop() = default;

    void render(SDL_Renderer* renderer, int xOffset, int yOffset);

    void setOpen(bool open);
    void setSpritesheet(Spritesheet* spritesheet);

    bool isOpen();
    int getWidth();
    int getHeight();

private:
    SDL_Point _position = {0, 12};
    bool _opened = false;
    SDL_Point _size = {0, 0};
    SDL_Point _maxSize = {32, 120};

    Spritesheet* _shopSpritesheet = nullptr;
    
    // Items in shop inventory
    std::vector<std::shared_ptr<Object>> _inventory;
};

#endif