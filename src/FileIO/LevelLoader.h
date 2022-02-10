#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <vector>
#include <string>

class LevelLoader {
public:
    LevelLoader() = default;
    ~LevelLoader() = default;

    static std::vector<std::vector<int>> loadLevel(std::string path);

private:

};

#endif