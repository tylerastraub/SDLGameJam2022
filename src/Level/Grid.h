#ifndef GRID_H
#define GRID_H

#include "Edge.h"
#include "Object.h"
#include "Square.h"
#include "RightTriangle.h"
#include "LongRightTriangle.h"
#include "Diamond.h"

#include <list>
#include <vector>
#include <memory>

class Grid {
public:
    Grid(int tileSize);
    Grid(int tileSize, int gridWidth, int gridHeight);
    ~Grid() = default;

    // Goes through all tiles that edge (possibly) intersects and adds the edge coordinate to said tile
    void addEdge(Edge edge);
    void addObject(std::shared_ptr<Square> square);
    void addObject(std::shared_ptr<RightTriangle> triangle);
    void addObject(std::shared_ptr<LongRightTriangle> triangle);
    void addObject(std::shared_ptr<Diamond> diamond);

    void setGridSize(int w, int h);
    void setTileset(Spritesheet* tileset);

    int getGridWidth();
    int getGridHeight();
    int getTileSize();
    // Retrieve all edges stored in a grid cell
    std::list<Edge> getEdges(int x, int y);
    std::list<std::shared_ptr<Object>> getObjects();
    // Get all grid coordinates that intersect with a line
    std::vector<SDL_Point> getGridCellsIntersectingWithLine(const SDL_Point p1, const SDL_Point p2);

private:
    SDL_Point findWhereLinesIntersect(SDL_Point l1_start, SDL_Point l1_target, SDL_Point l2_start, SDL_Point l2_target);
    // Gets frac of float (works for negative numbers)
    float getFrac(float f);

    int _tileSize = 0;
    int _gridWidth = 0;
    int _gridHeight = 0;

    // Map of all edges stored by tile coordinate. Use getEdges() to retrieve them
    std::vector<std::list<Edge>> _edgeMap;
    // List of all objects in grid
    std::list<std::shared_ptr<Object>> _objectList;

    Spritesheet* _tileset = nullptr;

};

#endif