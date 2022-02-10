#ifndef RESET_BUTTON_H
#define RESET_BUTTON_H

#include "Button.h"
#include "Shop.h"

class ResetButton : public Button {
public:
    ResetButton();
    ~ResetButton() = default;

    void onClick() override;
    void render(int xOffset, int yOffset) override;

    void setsRequestsReset(bool requestsReset);
    void setShop(Shop* shop);

    bool requestsReset();

private:
    bool _requestReset = false;

    Shop* _shop;

};

#endif