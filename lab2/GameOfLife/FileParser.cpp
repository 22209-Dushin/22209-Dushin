#include <iostream>
#include <sstream>
#include "FileParser.h"

int FileParser::parse(std::string inFileName, GameData& gameData) {
    if (inFileName.empty())
        return 0;

    std::ifstream file(inFileName);

    if (!file) {
        std::cerr << "Failed to open input file: " << inFileName << std::endl;
        return 1;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            std::stringstream ss(line.substr(1));
            char type;
            ss >> type;

            switch (type) {
                case 'N':
                    ss >> gameData.name;
                    break;
                case 'R':
                    ss >> gameData.rules;
                    break;
            }
        } else {
            std::stringstream ss(line);
            Point Coordinate;
            ss >> Coordinate.x >> Coordinate.y;
            gameData.aliveCells.push_back(Coordinate);
            gameData.maxX = std::max(Coordinate.x, gameData.maxX);
            gameData.maxY = std::max(Coordinate.y, gameData.maxY);
        }
    }
    return 0;
}
