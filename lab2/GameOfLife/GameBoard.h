#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"
#include "State.h"

class GameBoard {
private:
    int width;
    int height;
    int shiftX = 0;
    int shiftY = 0;
    std::vector<State> board;

public:
    GameBoard(std::vector<Point> coordinates, int maxY, int maxX, int minY, int minX);
    GameBoard(int maxY, int maxX, int minY, int minX);

    void fillDead();
    
    void fillRandom();

    State& operator()(int x, int y);

    GameBoard& operator=(const GameBoard& other);

    int getHeight() const;
    
    int getWidth() const;
    
    int getMinX() const;
    
    int getMinY() const;
};

#endif
