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
};