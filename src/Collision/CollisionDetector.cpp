#include "CollisionDetector.h"

#include <queue>
#include <cmath>
#include <chrono>
#include <iostream>
#include <algorithm>

// Use raycast to find first collision, calculate angle based on edge it collides with, increment bounces, then start calculating next line
std::vector<SDL_Point> CollisionDetector::calculateShotPath(Grid grid, SDL_Point start, SDL_Point target, int numOfBounces) {
    std::vector<SDL_Point> result;
    int bounces = 0;
    SDL_Point currentLineStart = start;
    SDL_Point currentLineTarget = target;
    // Calculate each line
    while(bounces <= numOfBounces) {
        // std::cout << bounces << ": Starting at (" << currentLineStart.x << ", " << currentLineStart.y
        // << "), ending at (" << currentLineTarget.x << ", " << currentLineTarget.y << ")" << std::endl;
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
                // instead of this quick fix (which is likely causing perpendicular angle bug) can just look at normal vec to move next line start by 1 pixel out of collided edge
            //    (collision.x != currentLineStart.x && collision.y != currentLineStart.y)) {
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
        SDL_Point normalVec;
        currentLineTarget = calculateNextTargetAfterBounce(grid, currentLineStart, collisionPoint, collidedEdge, normalVec);
        if(normalVec.x > 0) normalVec.x = 1; else if(normalVec.x < 0) normalVec.x = -1;
        if(normalVec.y > 0) normalVec.y = 1; else if(normalVec.y < 0) normalVec.y = -1;
        currentLineStart = {collisionPoint.x + normalVec.x, collisionPoint.y + normalVec.y};

        ++bounces;
    }

    return result;
}

void CollisionDetector::checkForShotEntityCollisions(Projectile* shot, std::list<Entity*> entities) {
    SDL_Rect shotRect = shot->getCollisionRect();
    bool collision = false;
    for(auto e : entities) {
        SDL_Rect entityRect = e->getCollisionRect();
        if(SDL_HasIntersection(&shotRect, &entityRect)) {
            collision = true;
            e->collisionEvent();
        }
    }
    if(collision) shot->collisionEvent();
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

    // Weird edge cases handled here
    if((points[0].x != start.x && points[0].y != start.y) ||
       (target.x - start.x < 0 && target.y == start.y) ||
       (target.y - start.y < 0 && target.x == start.x)) {
        std::reverse(points.begin(), points.end());
    }

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
    float l1_dx = l1_target.x - l1_start.x;
    float l1_dy = l1_target.y - l1_start.y;
    float l2_dx = l2_target.x - l2_start.x;
    float l2_dy = l2_target.y - l2_start.y;

    float s, t;
    s = (-l1_dy * (l1_start.x - l2_start.x) + l1_dx * (l1_start.y - l2_start.y)) / (-l2_dx * l1_dy + l1_dx * l2_dy);
    t = ( l2_dx * (l1_start.y - l2_start.y) - l2_dy * (l1_start.x - l2_start.x)) / (-l2_dx * l1_dy + l1_dx * l2_dy);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        SDL_Point collision = {l1_start.x + (int) (t * l1_dx), l1_start.y + (int) (t * l1_dy)};
        return collision;
    }

    // No collision
    return {-1, -1};
}

// Referenced https://stackoverflow.com/questions/573084/how-to-calculate-bounce-angle
SDL_Point CollisionDetector::calculateNextTargetAfterBounce(Grid grid, SDL_Point shotStart, SDL_Point shotEnd, Edge edge, SDL_Point& normalVec) {
    int shotDX = shotEnd.x - shotStart.x;
    int shotDY = shotEnd.y - shotStart.y;
    int edgeDX = edge.p2.x - edge.p1.x;
    int edgeDY = edge.p2.y - edge.p1.y;
    
    // Determine which normal vector points in direction we want
    SDL_Point potNormalVec1 = {(int) (edgeDY * -1.f), (int) edgeDX};
    SDL_Point potNormalVec2 = {(int) edgeDY, (int) (edgeDX * -1.f)};
    SDL_Point normalVecOffset, vecComponentU, vecComponentW, newVec;
    if(std::hypot(shotDX + potNormalVec1.x, shotDY + potNormalVec1.y)
        < std::hypot(shotDX + potNormalVec2.x, shotDY + potNormalVec2.y)) {
        normalVecOffset = potNormalVec1;
    }
    else {
        normalVecOffset = potNormalVec2;
    }
    normalVec = normalVecOffset;

    // Find new vector using dot product. Note that U is perpendicular to the wall and W is parallel
    float dotProductN = calculateDotProduct({shotDX, shotDY}, normalVecOffset) / calculateDotProduct(normalVecOffset, normalVecOffset);
    vecComponentU = {(int) (normalVecOffset.x * dotProductN), (int) (normalVecOffset.y * dotProductN)};
    vecComponentW = {shotDX - vecComponentU.x, shotDY - vecComponentU.y};
    newVec = {vecComponentW.x - vecComponentU.x, vecComponentW.y - vecComponentU.y};

    float magnitude = (float) grid.getGridWidth() * grid.getTileSize() / std::hypot(newVec.x, newVec.y);
    return {(int) (shotEnd.x + newVec.x * magnitude), (int) (shotEnd.y + newVec.y * magnitude)};
}

float CollisionDetector::calculateDotProduct(SDL_Point v1, SDL_Point v2) {
    return v1.x * v2.x + v1.y * v2.y;
}