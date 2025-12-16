#ifndef OOP_MAPGENERATOR_H
#define OOP_MAPGENERATOR_H

#include <vector>
#include "Target.h"

class MapGenerator {
public:
    static std::vector<Target> generateClassicLevel();
    static std::vector<Target> generateWallLevel();
    static std::vector<Target> generatePyramidLevel();
    static std::vector<Target> generateRandomChaos();
};

#endif