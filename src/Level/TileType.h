enum TileType {
    // Empty tile. No collisions - essentially a background tile
    EMPTY = 0,
    // Completely solid tile
    SQUARE = 1,
    // Right triangle facing north
    RIGHT_TRIANGLE_NORTH = 2,
    // Right triangle facing east
    RIGHT_TRIANGLE_EAST = 3,
    // Right triangle facing south
    RIGHT_TRIANGLE_SOUTH = 4,
    // Right triangle facing west
    RIGHT_TRIANGLE_WEST = 5,
    // Four sided diamond
    DIAMOND = 6,
    // Long right triangle facing north
    LONG_RIGHT_TRIANGLE_NORTH = 7,
    // Long right triangle facing east
    LONG_RIGHT_TRIANGLE_EAST = 8,
    // Long right triangle facing south
    LONG_RIGHT_TRIANGLE_SOUTH = 9,
    // Long right triangle facing west
    LONG_RIGHT_TRIANGLE_WEST = 10,
    // Level goal
    GOAL_TILE = 11,
};