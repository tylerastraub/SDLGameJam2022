#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "Edge.h"
#include "Grid.h"

#include <vector>

// Helper class used to resolve collisions between entities as well as entities with the level.
class CollisionDetector {
public:
    CollisionDetector() = default;
    ~CollisionDetector() = default;

    /**
     * @brief Calulate the path a shot will take then return said path in a vector of points.
     * 
     * @param start The start coordinates of the shot
     * @param target The target coordinates of the shot
     * @param numOfBounces How many bounces to calculate in shot.
     * @return std::vector<SDL_Point> containing all points on said path
     */
    std::vector<SDL_Point> calculateShotPath(Grid grid, SDL_Point start, SDL_Point target, int numOfBounces);

private:
    /**
     * @brief Returns all points in a line given start and target coordinates. Note that if line's slop is less than y=x, start/target coordinates will reverse
     * 
     * @param start The start coordinates of the line
     * @param target The target coordinates of the line
     * @return std::vector<SDL_Point> 
     */
    std::vector<SDL_Point> calculateLinePath(SDL_Point start, SDL_Point target);

    /**
     * @brief Determines whether or not 2 lines are intersecting at any point
     * 
     * @param l1_start Line 1's start point
     * @param l1_target Line 1's end point
     * @param l2_start Line 2's start point
     * @param l2_target Line 2's end point
     * @return bool
     */
    bool linesAreIntersecting(SDL_Point l1_start, SDL_Point l1_target, SDL_Point l2_start, SDL_Point l2_target);

    /**
     * @brief Determines whether a point lies on a line between two points.
     * 
     * @param lineStart First point in line
     * @param lineEnd Last point in line
     * @param point Point to test whether it exists on line or not
     * @return true 
     * @return false 
     */
    bool pointIsOnLine(SDL_Point lineStart, SDL_Point lineEnd, SDL_Point point);

    /** 
     * @brief Determines whether or not there is an intersection between two lines and, if so, returns where the two lines intersect.
     * 
     * @return Returns {-1, -1} if no intersection is found. Otherwise, returns the point of intersection.
     */
    SDL_Point findWhereLinesIntersect(SDL_Point l1_start, SDL_Point l1_target, SDL_Point l2_start, SDL_Point l2_target);

    /**
     * @brief Given a line colliding with an edge, find the target of the next line
     * 
     * @param shotStart The starting point of the shot
     * @param shotEnd The ending point of the shot
     * @param edge The edge the shot is colliding with
     * @return SDL_Point 
     */
    SDL_Point calculateNextTargetAfterBounce(Grid grid, SDL_Point shotStart, SDL_Point shotEnd, Edge edge);

    float calculateDotProduct(SDL_Point v1, SDL_Point v2);

};

#endif