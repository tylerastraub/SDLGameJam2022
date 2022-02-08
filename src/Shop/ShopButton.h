#ifndef SHOP_BUTTON_H
#define SHOP_BUTTON_H

#include "Button.h"
#include "Shop.h"

class ShopButton : public Button {
public:
    ShopButton();
    ~ShopButton() = default;

    void onClick() override;
    void render(int xOffset, int yOffset) override;

    void setShop(Shop* shop);

    Shop* getShop();

private:
    Shop* _shop = nullptr;

};

#endif