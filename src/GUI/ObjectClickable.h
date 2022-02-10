#ifndef OBJECT_BUTTON_H
#define OBJECT_BUTTON_H

#include "Clickable.h"
#include "Object.h"

#include <memory>

class ObjectClickable : public Clickable {
public:
    ObjectClickable(TileType tileType);
    ~ObjectClickable() = default;
    
    void onLeftMouseButtonDown() override;
    void onLeftMouseButtonUp() override;
    void render(int xOffset, int yOffset) override {};

    void resetDefaultPosition();
    void rotateRight();

    void setDefaultPosition(int x, int y);
    void clearObject();

    std::shared_ptr<Object> getObject();
    TileType getTileType();

private:
    SDL_Point _defaultPosition = {0, 0};
    std::shared_ptr<Object> _object = nullptr;
    TileType _tileType = TileType::EMPTY;
};

#endif