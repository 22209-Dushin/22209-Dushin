#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "GameBoard.h"
#include "GameData.h"

class Game {
private:
    std::string name;
    GameBoard board;
    GameBoard lastBoard;

    std::vector<bool> bornRules;
    std::vector<bool> surviveRules;

    int countNeighbours(int x, int y);

public:
    Game(GameData gameData);

    std::string getName() const;

    const GameBoard& getBoard() const;
    
    std::string getRules() const;

    void createRandomBoard();
    void updateBoard();
    bool checkCell(int x, int y) const;
};

#endif
