#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <string>
#include <fstream>
#include "GameData.h"

class FileParser {
public:
    int parse(std::string inFileName, GameData& gameData);
};

#endif
