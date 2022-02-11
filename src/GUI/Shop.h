#ifndef SHOP_H
#define SHOP_H

#include "Spritesheet.h"
#include "Object.h"
#include "ObjectClickable.h"

#include <vector>
#include <list>
#include <memory>

class Shop {
public:
    Shop();
    ~Shop() = default;

    void render(SDL_Renderer* renderer, int xOffset, int yOffset);
    void resetMoney();

    void setOpen(bool open);
    void setSpritesheet(Spritesheet* spritesheet);
    void setMoney(int money);
    void setStartingMoney(int startingMoney);

    bool isOpen();
    int getWidth();
    int getHeight();
    int getMoney();
    std::list<std::shared_ptr<Clickable>> getObjectBuyButtons();

private:
    SDL_Point _position = {0, 12};
    bool _opened = false;
    SDL_Point _size = {0, 0};
    SDL_Point _maxSize = {32, 120};

    Spritesheet* _shopSpritesheet = nullptr;
    
    // Items in shop inventory
    std::vector<std::shared_ptr<Object>> _inventory;
    // Buttons for buying objects
    std::list<std::shared_ptr<Clickable>> _objectBuyButtons;
    // Starting money. _money is set to this upon reset
    int _startingMoney = 3;
    // How much money is available to spend
    int _money = 3;
};

#endif