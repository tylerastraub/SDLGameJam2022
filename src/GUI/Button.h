#ifndef BUTTON_H
#define BUTTON_H

#include "Clickable.h"
#include "Spritesheet.h"

class Button : public Clickable {
public:
    Button() = default;
    ~Button() = default;

    virtual void onClick() = 0;
    virtual void render(int xOffset, int yOffset) override = 0;

    void onLeftMouseButtonDown() override;
    void onLeftMouseButtonUp() override;

private:

};

#endif