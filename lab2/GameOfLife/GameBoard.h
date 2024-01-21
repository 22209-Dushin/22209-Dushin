#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"
#include "State.h"

class GameBoard {
private:
    int width;
    int height;
    std::vector<State> board;

public:
    GameBoard(std::vector<Point> coordinates, int maxY, int maxX);
    GameBoard(int maxY, int maxX);

    void fillDead();
    void fillRandom();

    State& operator()(int x, int y);

    GameBoard& operator=(const GameBoard& other);

    int getHeight();
    int getWidth();
};

#endif
