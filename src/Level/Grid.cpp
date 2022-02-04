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

int Grid::getGridWidth() {
    return _gridWidth;
}

int Grid::getGridHeight() {
    return _gridHeight;
}

int Grid::getTileSize() {
    return _tileSize;
}

std::list<Edge> Grid::getEdges(int x, int y) {
    if(x >= _gridWidth || x < 0 || y >= _gridHeight || y < 0) {
        // std::cout << "Error: invalid grid coordinates at (" << x << ", " << y << ")" << std::endl;
        return std::list<Edge>();
    }
    return _edgeMap[y * _gridWidth + x];
}

std::vector<SDL_Point> Grid::getGridCellsIntersectingWithLine(const SDL_Point p1, const SDL_Point p2) {
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

// Code from https://stackoverflow.com/a/1968345
SDL_Point Grid::findWhereLinesIntersect(SDL_Point l1_start, SDL_Point l1_target, SDL_Point l2_start, SDL_Point l2_target) {
    float s1_x = l1_target.x - l1_start.x;
    float s1_y = l1_target.y - l1_start.y;
    float s2_x = l2_target.x - l2_start.x;
    float s2_y = l2_target.y - l2_start.y;

    float s, t;
    s = (-s1_y * (l1_start.x - l2_start.x) + s1_x * (l1_start.y - l2_start.y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (l1_start.y - l2_start.y) - s2_y * (l1_start.x - l2_start.x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        SDL_Point collision = {l1_start.x + (int) (t * s1_x), l1_start.y + (int) (t * s1_y)};
        return collision;
    }

    // No collision
    return {-1, -1};
}