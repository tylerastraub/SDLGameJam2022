#include "ObjectClickable.h"

#include "Square.h"
#include "RightTriangle.h"
#include "LongRightTriangle.h"
#include "Diamond.h"

ObjectClickable::ObjectClickable(ObjectType objectType) : _objectType(objectType) {}

void ObjectClickable::onLeftMouseButtonDown() {
    if(_object == nullptr) {
        switch(_objectType) {
            case(ObjectType::OBJECT_SQUARE): {
                _object = std::make_shared<Square>(ObjectDirection::NORTH);
                break;
            }
            case(ObjectType::OBJECT_RIGHT_TRIANGLE): {
                _object = std::make_shared<RightTriangle>(ObjectDirection::NORTH);
                break;
            }
            case(ObjectType::OBJECT_LONG_RIGHT_TRIANGLE): {
                _object = std::make_shared<LongRightTriangle>(ObjectDirection::EAST);
                break;
            }
            case(ObjectType::OBJECT_DIAMOND): {
                _object = std::make_shared<Diamond>(ObjectDirection::NORTH);
                break;
            }
        }
        _object->setPosition(getPosition().x - _object->getNaturalSize().x / 2,
            getPosition().y - _object->getNaturalSize().y / 2);
        _object->setDrawShadows(false);
        _object->setMoveable(true);
        _object->setInGrid(false);
    }
}

void ObjectClickable::onLeftMouseButtonUp() {
    if(_object) {
        _object = nullptr;
    }
}

void ObjectClickable::resetDefaultPosition() {
    setPosition(_defaultPosition.x, _defaultPosition.y);
}

void ObjectClickable::setDefaultPosition(int x, int y) {
    _defaultPosition = {x, y};
}

std::shared_ptr<Object> ObjectClickable::getObject() {
    return _object;
}

ObjectType ObjectClickable::getObjectType() {
    return _objectType;
}