#include "LevelLoader.h"
#include "FileIO.h"

std::vector<std::vector<int>> LevelLoader::loadLevel(std::string path) {
    const int MAX_LEVEL_WIDTH = 20;
    const int MAX_LEVEL_HEIGHT = 12;
    std::vector<std::vector<int>> result;
    std::vector<std::string> levelTxt = FileIO::readFile(path);
    int columnCounter = 0;
    for(std::string line : levelTxt) {
        std::vector<int> row;
        for(int x = 0; x < MAX_LEVEL_WIDTH; ++x) {
            if(line.empty()) {
                while(x < MAX_LEVEL_WIDTH) {
                    row.push_back(-1);
                    ++x;
                }
                break;
            }
            std::string tile = line.substr(0, line.find_first_of(','));
            row.push_back(std::stoi(tile));
            line.erase(line.begin(), line.begin() + line.find_first_of(',') + 1);
        }
        result.push_back(row);
        ++columnCounter;
        if(columnCounter >= MAX_LEVEL_HEIGHT) break;
    }

    return result;
}