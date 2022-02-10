#include "Button.h"

void Button::onLeftMouseButtonDown() {
    setClicked(true);
}

void Button::onLeftMouseButtonUp() {
    if(isClicked()) {
        setClicked(false);
        onClick();
    }
}