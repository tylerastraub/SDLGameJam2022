#include "CollisionDetector.h"

#include <queue>
#include <cmath>
#include <chrono>
#include <iostream>
#include <algorithm>

// TODO: https://stackoverflow.com/questions/573084/how-to-calculate-bounce-angle
// Use raycast to find first collision, calculate angle based on edge it collides with, increment bounces, then start calculating next line
std::vector<SDL_Point> CollisionDetector::calculateShotPath(Grid grid, SDL_Point start, SDL_Point target, int numOfBounces) {
    std::vector<SDL_Point> result;
    int bounces = 0;
    SDL_Point currentLineStart = start;
    SDL_Point currentLineTarget = target;
    // Calculate each line
    while(bounces <= numOfBounces) {
        SDL_Point collisionPoint = {-1, -1};
        std::vector<SDL_Point> shotLine = calculateLinePath(currentLineStart, currentLineTarget);
        std::vector<SDL_Point> cellsInPath = grid.getGridCellsIntersectingWithLine(currentLineStart, currentLineTarget);
        std::vector<Edge> collidingEdges;
        // Find all colliding edges
        for(SDL_Point cell : cellsInPath) {
            std::list<Edge> edges = grid.getEdges(cell.x, cell.y);
            if(edges.size() > 0) {
                for(auto it = edges.begin(); it != edges.end(); ++it) {
                    if(linesAreIntersecting(currentLineStart, currentLineTarget, it->p1, it->p2)) {
                        collidingEdges.push_back(*it);
                    }
                }
            }
        }
        // Then determine which one was actually first
        for(SDL_Point linePoint : shotLine) {
            if(collisionPoint.x != -1 && collisionPoint.y != -1) break;
            for(Edge edge : collidingEdges) {
                if(pointIsOnLine(edge.p1, edge.p2, linePoint)) {
                    collisionPoint = linePoint;
                }
                else if(linesAreIntersecting(linePoint, linePoint, edge.p1, edge.p2)) {
                    collisionPoint = linePoint;
                }
            }
        }
        // If no collision, just append current line and return
        if(collisionPoint.x == -1 && collisionPoint.y == -1) {
            result.insert(result.end(), shotLine.begin(), shotLine.end());
            return result;
        }

        // Add current line
        std::vector<SDL_Point> newLine = calculateLinePath(currentLineStart, collisionPoint);
        result.insert(result.end(), newLine.begin(), newLine.end());
        // Then determine angle of next line

        ++bounces;
    }

    return result;
}

std::vector<SDL_Point> CollisionDetector::calculateLinePath(SDL_Point start, SDL_Point target) {
    std::vector<SDL_Point> points;
    int x0 = start.x;
    int x1 = target.x;
    int y0 = start.y;
    int y1 = target.y;
    // Bresenham line algorithm
    // Code taken from https://www.codeproject.com/Articles/15604/Ray-casting-in-a-2D-tile-based-environment
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if(steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if(x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int deltaX = x1 - x0;
    int deltaY = std::abs(y1 - y0);
    int error = 0;
    int y = y0;
    int yStep;
    if(y0 < y1) yStep = 1;
    else yStep = -1;
    for(int x = x0; x <= x1; ++x) {
        if(steep) {
            points.push_back({y, x});
        }
        else {
            points.push_back({x, y});
        }
        error += deltaY;
        if(2 * error >= deltaX) {
            y += yStep;
            error -= deltaX;
        }
    }

    if(points[0].x != start.x && points[0].y != start.y) std::reverse(points.begin(), points.end());

    return points;
}

// Code taken from https://gamedev.stackexchange.com/questions/26004/how-to-detect-2d-line-on-line-collision
bool CollisionDetector::linesAreIntersecting(SDL_Point l1_start, SDL_Point l1_target, SDL_Point l2_start, SDL_Point l2_target) {
    float denominator = ((l1_target.x - l1_start.x) * (l2_target.y - l2_start.y)) - ((l1_target.y - l1_start.y) * (l2_target.x - l2_start.x));
    float numerator1 = ((l1_start.y - l2_start.y) * (l2_target.x - l2_start.x)) - ((l1_start.x - l2_start.x) * (l2_target.y - l2_start.y));
    float numerator2 = ((l1_start.y - l2_start.y) * (l1_target.x - l1_start.x)) - ((l1_start.x - l2_start.x) * (l1_target.y - l1_start.y));

    // Detect coincident lines (has a problem, read below)
    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;
    
    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

// Code taken from https://stackoverflow.com/a/11908158
bool CollisionDetector::pointIsOnLine(SDL_Point lineStart, SDL_Point lineEnd, SDL_Point point) {
    int dxc = point.x - lineStart.x;
    int dyc = point.y - lineStart.y;

    int dxl = lineEnd.x - lineStart.x;
    int dyl = lineEnd.y - lineStart.y;

    int cross = dxc * dyl - dyc * dxl;

    if(cross != 0) return false;

    if (std::abs(dxl) >= std::abs(dyl))
        return dxl > 0 ? 
            lineStart.x <= point.x && point.x <= lineEnd.x :
            lineEnd.x <= point.x && point.x <= lineStart.x;
    else
        return dyl > 0 ? 
            lineStart.y <= point.y && point.y <= lineEnd.y :
            lineEnd.y <= point.y && point.y <= lineStart.y;
}