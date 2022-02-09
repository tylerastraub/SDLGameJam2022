#ifndef OBJECT_BUTTON_H
#define OBJECT_BUTTON_H

#include "Clickable.h"
#include "Object.h"

#include <memory>

class ObjectClickable : public Clickable {
public:
    ObjectClickable(ObjectType objectType);
    ~ObjectClickable() = default;
    
    void onLeftMouseButtonDown() override;
    void onLeftMouseButtonUp() override;
    void render(int xOffset, int yOffset) override {};

    void resetDefaultPosition();

    void setDefaultPosition(int x, int y);

    std::shared_ptr<Object> getObject();
    ObjectType getObjectType();

private:
    SDL_Point _defaultPosition = {0, 0};
    std::shared_ptr<Object> _object = nullptr;
    ObjectType _objectType = ObjectType::OBJECT_NONE;
};

#endif