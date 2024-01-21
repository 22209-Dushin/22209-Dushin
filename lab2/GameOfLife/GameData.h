#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <vector>
#include "Point.h"

struct GameData {
    std::string name = "-----";
    std::string rules = "B3/S23";
    std::vector<Point> aliveCells;
    int maxX = 0;
    int maxY = 0;
};

#endif
