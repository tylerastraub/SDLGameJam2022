#include "Grid.h"

#include <iostream>
#include <cmath>

Grid::Grid(int tileSize) : _tileSize(tileSize) {}

Grid::Grid(int tileSize, int gridWidth, int gridHeight)
    : _gridWidth(gridWidth), _gridHeight(gridHeight), _tileSize(tileSize) {
    for(int i = 0; i < gridWidth * gridHeight; ++i) {
        _edgeMap.push_back(std::list<Edge>());
    }
}

void Grid::addEdge(Edge edge) {
    SDL_Point p1_tileCoords = {edge.p1.x / _tileSize, edge.p1.y / _tileSize};
    SDL_Point p2_tileCoords = {edge.p2.x / _tileSize, edge.p2.y / _tileSize};
    // TODO: Use raycast algorithm to determine which tiles edge goes through
    SDL_Point start, end;
    if(p1_tileCoords.x < p2_tileCoords.x) {
        start.x = p1_tileCoords.x;
        end.x = p2_tileCoords.x;
    }
    else {
        start.x = p2_tileCoords.x;
        end.x = p1_tileCoords.x;
    }
    if(p1_tileCoords.y < p2_tileCoords.y) {
        start.y = p1_tileCoords.y;
        end.y = p2_tileCoords.y;
    }
    else {
        start.y = p2_tileCoords.y;
        end.y = p1_tileCoords.y;
    }
    for(int x = start.x; x <= end.x; ++x) {
        for(int y = start.y; y <= end.y; ++y) {
            _edgeMap[y * _gridWidth + x].emplace_back(edge);
        }
    }
}

void Grid::setGridSize(int w, int h) {
    _gridWidth = w;
    _gridHeight = h;
    if(_edgeMap.empty()) {
        for(int i = 0; i < _gridWidth * _gridHeight; ++i) {
            _edgeMap.push_back(std::list<Edge>());
        }
    }
}

std::list<Edge> Grid::getEdges(int x, int y) {
    if(x >= _gridWidth || x < 0 || y >= _gridHeight || y < 0) {
        std::cout << "Error: invalid grid coordinates at (" << x << ", " << y << ")" << std::endl;
        return std::list<Edge>();
    }
    return _edgeMap[y * _gridWidth + x];
}

std::vector<SDL_Point> Grid::getGridCellsIntersectingWithLine(const SDL_Point p1, const SDL_Point p2) {
    if(p1.x < 0 || p1.x >= _gridWidth * _tileSize || p1.y < 0 || p1.y >= _gridHeight * _tileSize
       || p2.x < 0 || p2.x >= _gridWidth * _tileSize || p2.y < 0 || p2.y >= _gridHeight * _tileSize) {
        std::cout << "Error: line coordinates out of bounds! P1: (" << p1.x << ", " << p1.y << "), P2: (" << p2.x << ", " << p2.y << ")" << std::endl;
        return std::vector<SDL_Point>();
    }

    std::vector<SDL_Point> results;
    int x = p1.x / _tileSize;
    int y = p1.y / _tileSize;
    // Add start
    results.push_back({x, y});
    if(p1.x / _tileSize == p2.x / _tileSize && p1.y / _tileSize == p2.y / _tileSize) {
        return results;
    }
    int stepX = (p1.x <= p2.x) ? 1 : -1;
    int stepY = (p1.y <= p2.y) ? 1 : -1;
    float tDeltaX = (float) stepX / (float) (p2.x - p1.x) * (float) _tileSize;
    float tDeltaY = (float) stepY / (float) (p2.y - p1.y) * (float) _tileSize;
    float tMaxX = tDeltaX * getFrac((float) p1.x / (float) _tileSize * stepX);
    float tMaxY = tDeltaY * getFrac((float) p1.y / (float) _tileSize * stepY);
    // std::cout << "stepX: " << stepX <<", stepY: " << stepY << ", tMaxX: " << tMaxX << ", tMaxY: " << tMaxY << ", tDeltaX: " << tDeltaX << ", tDeltaY: " << tDeltaY << std::endl;
    do {
        if(tMaxX < tMaxY) {
            tMaxX += tDeltaX;
            x += stepX;
        }
        else {
            tMaxY += tDeltaY;
            y += stepY;
        }
        results.push_back({x, y});
        if (tMaxX > 1 && tMaxY > 1) break;
    }
    while(x >= 0 && x < _gridWidth && y >= 0 && y < _gridHeight);

    return results;
}

float Grid::getFrac(float f) {
    if(f > 0.f) {
        f = 1.f - f + std::floor(f);
        return f;
    }
    else {
        f -= std::floor(f);
        return f * -1.f + 1.f;
    }
}