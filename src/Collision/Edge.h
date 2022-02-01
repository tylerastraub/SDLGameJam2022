#ifndef EDGE_H
#define EDGE_H

#include <SDL.h>

// Line object used for collision detection. Represents a line covering the
// edge of a tile or object.
struct Edge {
    Edge(SDL_Point p1, SDL_Point p2);

    SDL_Point p1 = {0, 0};
    SDL_Point p2 = {0, 0};
};

#endif