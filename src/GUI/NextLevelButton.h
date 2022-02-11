#ifndef NEXT_LEVEL_BUTTON_H
#define NEXT_LEVEL_BUTTON_H

#include "Button.h"
#include "Shop.h"

class NextLevelButton : public Button {
public:
    NextLevelButton() = default;
    ~NextLevelButton() = default;

    void onClick() override;
    void render(int xOffset, int yOffset) override;

    void setEnabled(bool enabled);
    void setShop(Shop* shop);

    bool isEnabled();
    bool hasBeenClicked();

private:
    bool _isEnabled = false;
    bool _hasBeenClicked = false;
    Shop* _shop = nullptr;

};

#endif