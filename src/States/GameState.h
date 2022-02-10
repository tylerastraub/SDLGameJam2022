#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Mouse.h"
#include "Tilemap.h"
#include "CollisionDetector.h"
#include "Projectile.h"
#include "Clickable.h"
#include "Shop.h"

#include <memory>

class GameState : public State {
public:
    GameState() = default;
    ~GameState() = default;

    void init() override;
    void handleInput() override;
    void handleMouseInput(SDL_Event e) override;
    void tick(float timescale) override;
    void render() override;

    void addEntity(std::shared_ptr<Entity> entity);

private:
    std::unique_ptr<Mouse> _mouse = nullptr;
    std::unique_ptr<Tilemap> _tilemap = nullptr;
    // The base for the tilemap. Used for resetting so we remember what OG tilemap looked like
    std::unique_ptr<Tilemap> _defaultTilemap = nullptr;
    std::unique_ptr<Grid> _grid = nullptr;
    CollisionDetector _collisionDetector;

    // The path displayed for the guide line
    std::vector<SDL_Point> _guideLineShotPath;
    // The actual path the bullet will take
    std::vector<SDL_Point> _shotPath;
    // How many bounces to display for guide line
    int _numOfGuideLineBounces = 1;
    // How many bounces the shot should actually do
    int _numOfBounces = 10;

    Projectile* _shot = nullptr;
    SDL_Point _shotStart = {336, 180};

    // Offset used for rendering. Shifts entire screen
    SDL_Point _renderOffset = {0, -12};

    // Whether or not to render the grid underlay. Used for build mode
    bool _renderGrid = true;

    // List of clickable objects. Include buttons, items, etc.
    std::list<std::shared_ptr<Clickable>> _clickables;
    // The shop object
    std::unique_ptr<Shop> _shop = nullptr;

    std::shared_ptr<Object> _currentObjSelection = nullptr;
    ObjectClickable* _currentOC = nullptr;

    // Keyboard
    bool _lastFramePressingR = false;
    bool _pressingR = false;
};

#endif