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
        std::cout << bounces << std::endl;
        SDL_Point collisionPoint = {-1, -1};
        Edge collidedEdge = {{-1, -1}, {-1, -1}};
        std::vector<SDL_Point> shotLine = calculateLinePath(currentLineStart, currentLineTarget);
        std::vector<SDL_Point> cellsInPath = grid.getGridCellsIntersectingWithLine(currentLineStart, currentLineTarget);
        std::vector<Edge> potentialEdges;
        // Find all potential colliding edges
        for(SDL_Point cell : cellsInPath) {
            std::list<Edge> edges = grid.getEdges(cell.x, cell.y);
            if(edges.size() > 0) {
                potentialEdges.insert(potentialEdges.end(), edges.begin(), edges.end());
            }
        }
        
        // Go cell by cell to find which edges are colliding, then determine which was first
        std::vector<std::pair<Edge, SDL_Point>> collisionPoints;
        collisionPoints.reserve(potentialEdges.size());
        for(Edge edge : potentialEdges) {
            SDL_Point collision = findWhereLinesIntersect(edge.p1, edge.p2, currentLineStart, currentLineTarget);
            if(collision.x != -1 && collision.y != -1) {
                collisionPoints.push_back({edge, collision});
            }
        }

        // If no collision, just append current line and return
        if(collisionPoints.empty()) {
            result.insert(result.end(), shotLine.begin(), shotLine.end());
            return result;
        }
        // Else if there's only 1 collision we can just go straight to it
        else if(collisionPoints.size() == 1) {
            collidedEdge = collisionPoints.begin()->first;
            collisionPoint = collisionPoints.begin()->second;
        }
        // If there are multiple collisions, we just go through them all and find the nearest one
        else {
            auto it = collisionPoints.begin();
            collidedEdge = it->first;
            SDL_Point p = it->second;
            float distance = std::hypot(currentLineStart.x - p.x, currentLineStart.y - p.y);
            ++it;
            for(; it != collisionPoints.end(); ++it) {
                float newDistance = std::hypot(currentLineStart.x - it->second.x, currentLineStart.y - it->second.y);
                if(newDistance < distance) {
                    collidedEdge = it->first;
                    p = it->second;
                }
            }
            collisionPoint = p;
        }

        // Calculate and add new line to the result
        std::vector<SDL_Point> newLine = calculateLinePath(currentLineStart, collisionPoint);
        result.insert(result.end(), newLine.begin(), newLine.end());
        // Then determine angle of next line
        currentLineTarget = calculateNextTargetAfterBounce(grid, currentLineStart, currentLineTarget, collidedEdge);
        currentLineStart = collisionPoint;

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

// Code from https://stackoverflow.com/a/1968345
SDL_Point CollisionDetector::findWhereLinesIntersect(SDL_Point l1_start, SDL_Point l1_target, SDL_Point l2_start, SDL_Point l2_target) {
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

SDL_Point CollisionDetector::calculateNextTargetAfterBounce(Grid grid, SDL_Point shotStart, SDL_Point shotEnd, Edge edge) {
    float shotDX = shotEnd.x - shotStart.x;
    float shotDY = shotEnd.y - shotStart.y;
    float edgeDX = edge.p2.x - edge.p1.x;
    float edgeDY = edge.p2.y - edge.p1.y;
    
    // Determine which normal vector points in direction we want
    SDL_Point potNormalVec1 = {(int) (edgeDY * -1.f), (int) edgeDX};
    SDL_Point potNormalVec2 = {(int) edgeDY, (int) (edgeDX * -1.f)};
    SDL_Point normalVec, normalVecOffset;
    if(std::hypot(shotDX + potNormalVec1.x, shotDY + potNormalVec1.y)
        < std::hypot(shotDX + potNormalVec2.x, shotDY + potNormalVec2.y)) {
        normalVecOffset = potNormalVec1;
    }
    else {
        normalVecOffset = potNormalVec2;
    }
    // std::cout << "Normal vec 1: " << potNormalVec1.x << ", " << potNormalVec1.y
    //     << " ; Normal vec 2: " << potNormalVec2.x << ", " << potNormalVec2.y
    //     << " ; Actual normal vec: " << normalVecOffset.x << ", " << normalVecOffset.y << std::endl;

    // Relocate normal vector so that it's hitting the collision point
    float normalVecMagnitude = std::hypot(edgeDX, edgeDY);
    float normalVecXMagnitude, normalVecYMagnitude;
    if(normalVecOffset.x < 0) {
        normalVecXMagnitude = (float) shotEnd.x / normalVecMagnitude;
    }
    else {
        normalVecXMagnitude = (float) (grid.getGridWidth() - shotEnd.x) / normalVecMagnitude;
    }
    // float normalVecXMagnitude = (normalVecOffset.x < 0) ? (float) shotEnd.x / normalVecMagnitude : (float) (grid.getGridWidth() - shotEnd.x) / normalVecMagnitude;
    normalVecYMagnitude = (normalVecOffset.y > 0) ? (float) shotEnd.y / normalVecMagnitude : (float) (grid.getGridHeight() - shotEnd.y) / normalVecMagnitude;
    normalVec = {shotEnd.x + normalVecOffset.x, shotEnd.y + normalVecOffset.y};
    std::cout << "Collision point: " << shotEnd.x << ", " << shotEnd.y
        << " ; Normal Vec: " << normalVec.x << ", " << normalVec.y << std::endl;
    // std::cout << "X Magnitude: " << normalVecXMagnitude << ", Y Magnitude: " << normalVecYMagnitude << std::endl;

    // Determine which quadrant we're in
    // if(shotDX >= 0 && shotDY < 0) {
    //     // Top right
    //     std::cout << "top right" << std::endl;
    // }
    // else if(shotDX < 0 && shotDY < 0) {
    //     // Top left
    //     std::cout << "top left" << std::endl;
    // }
    // else if(shotDX < 0 && shotDY >= 0) {
    //     // Bottom left
    //     std::cout << "bottom left" << std::endl;
    // }
    // else {
    //     // Bottom right
    //     std::cout << "bottom right" << std::endl;
    // }

    // std::cout << angle * (180.0 / M_PI) << " degrees" << std::endl;
    // std::cout << angle << "rad" << std::endl;
    // Find shot target using angle
    // double compAngle = (M_PI / 2) - std::abs(angle);
    // compAngle *= (angle < 0) ? -1.0 : 1.0;
    // std::cout << compAngle * (180.0 / M_PI) << std::endl;
    // std::cout << normalVecLength << std::endl;
    // SDL_Point coord = {(int) (32 * std::sin(angle)), int (32 * std::cos(angle))};
    // std::cout << normalVec.x << ", " << normalVec.y << std::endl;

    return {normalVec.x, normalVec.y};
}