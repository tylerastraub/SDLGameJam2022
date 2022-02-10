#include "Shop.h"
#include "Square.h"
#include "RightTriangle.h"
#include "Diamond.h"
#include "LongRightTriangle.h"

Shop::Shop() {
    _inventory.push_back(std::make_shared<Square>(ObjectDirection::NORTH));
    _inventory[0]->setRenderSize(16, 16);
    _inventory[0]->setDrawShadows(false);
    _inventory.push_back(std::make_shared<RightTriangle>(ObjectDirection::NORTH));
    _inventory[1]->setRenderSize(16, 16);
    _inventory[1]->setDrawShadows(false);
    _inventory.push_back(std::make_shared<LongRightTriangle>(ObjectDirection::NORTH));
    _inventory[2]->setRenderSize(8, 16);
    _inventory[2]->setDrawShadows(false);
    _inventory.push_back(std::make_shared<Diamond>(ObjectDirection::NORTH));
    _inventory[3]->setRenderSize(16, 16);
    _inventory[3]->setDrawShadows(false);

    std::shared_ptr<ObjectClickable> squareButton = std::make_shared<ObjectClickable>(TileType::SQUARE);
    squareButton->setClickRect({0, 0, 24, 24});
    squareButton->setPosition(-32, 0 + 16 + 12);
    _objectBuyButtons.emplace_back(squareButton);
    std::shared_ptr<ObjectClickable> rightTriangleButton = std::make_shared<ObjectClickable>(TileType::RIGHT_TRIANGLE_NORTH);
    rightTriangleButton->setClickRect({0, 0, 24, 24});
    rightTriangleButton->setPosition(-32, 28 + 16 + 12);
    _objectBuyButtons.emplace_back(rightTriangleButton);
    std::shared_ptr<ObjectClickable> longRightTriangleButton = std::make_shared<ObjectClickable>(TileType::LONG_RIGHT_TRIANGLE_NORTH);
    longRightTriangleButton->setClickRect({0, 0, 24, 24});
    longRightTriangleButton->setPosition(-32, 56 + 16 + 12);
    _objectBuyButtons.emplace_back(longRightTriangleButton);
    std::shared_ptr<ObjectClickable> diamondButton = std::make_shared<ObjectClickable>(TileType::DIAMOND);
    diamondButton->setClickRect({0, 0, 24, 24});
    diamondButton->setPosition(-32, 84 + 16 + 12);
    _objectBuyButtons.emplace_back(diamondButton);
}

void Shop::render(SDL_Renderer* renderer, int xOffset, int yOffset) {
    _shopSpritesheet->setIsAnimated(false);
    _shopSpritesheet->setIsLooped(false);
    SDL_Rect topRect = {0, 0, 32, 16 + (int) _inventory.size() * 28};
    SDL_SetRenderDrawColor(renderer, 0x4e, 0x58, 0x4a, 0xFF);
    SDL_RenderFillRect(renderer, &topRect);
    SDL_SetRenderDrawColor(renderer, 0x21, 0x21, 0x23, 0xFF);
    SDL_RenderDrawRect(renderer, &topRect);
    // Render coin
    _shopSpritesheet->setTileIndex(7, 2);
    _shopSpritesheet->setTileWidth(6);
    _shopSpritesheet->setTileHeight(8);
    _shopSpritesheet->setRenderWidth(6);
    _shopSpritesheet->setRenderHeight(8);
    _shopSpritesheet->render(_position.x + xOffset + 4, _position.y + yOffset + 4);
    for(int y = 0; y < _inventory.size(); ++y) {
        // Render tile
        _shopSpritesheet->setTileIndex(7, 1);
        _shopSpritesheet->setTileWidth(24);
        _shopSpritesheet->setTileHeight(24);
        _shopSpritesheet->setRenderWidth(24);
        _shopSpritesheet->setRenderHeight(24);
        _shopSpritesheet->render(_position.x + xOffset + 4, _position.y + y * 28 + yOffset + 16);
        // Render object
        Object* obj = _inventory[y].get();
        int yIndex = (obj->getNaturalSize().x > 32) ? 2 : 28;
        obj->render(_position.x + xOffset + 8, _position.y + y * yIndex + yOffset + 20);
    }
}

void Shop::setOpen(bool open) {
    _opened = open;
    if(_opened) {
        _size.x = _maxSize.x;
        _size.y = _maxSize.y;
        for(auto but : _objectBuyButtons) {
            but->setPosition(4, but->getPosition().y);
        }
    }
    else {
        _size = {0, 0};
        for(auto but : _objectBuyButtons) {
            but->setPosition(-32, but->getPosition().y);
        }
    }
}

void Shop::setSpritesheet(Spritesheet* spritesheet) {
    _shopSpritesheet = spritesheet;
    for(auto obj : _inventory) {
        obj->setObjectSpritesheet(spritesheet);
    }
}

void Shop::setMoney(int money) {
    _money = money;
}

bool Shop::isOpen() {
    return _opened;
}

int Shop::getWidth() {
    return _maxSize.x;
}

int Shop::getHeight() {
    return _maxSize.y;
}

int Shop::getMoney() {
    return _money;
}

std::list<std::shared_ptr<Clickable>> Shop::getObjectBuyButtons() {
    return _objectBuyButtons;
}