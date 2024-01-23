#include "GameBoard.h"
#include <cstdlib>

GameBoard::GameBoard(std::vector<Point> coordinates, int maxY, int maxX, int minY, int minX) {
	if (minX < 0) {
		shiftX = -minX;
	}
	if (minY < 0) {
		shiftY = -minY;
	}
		
	width = maxX + 1 + shiftX;
	height = maxY + 1 + shiftY;
	board.resize(width * height);
	
    fillDead();

    for (const auto& coord : coordinates) {
        int x = coord.x + shiftX;
        int y = coord.y + shiftY;
        (*this)(x, y) = State::Alive;
    }
}

GameBoard::GameBoard(int maxY, int maxX, int minY, int minX) {
    if (minX < 0) {
		shiftX = -minX;
	}
	if (minY < 0) {
		shiftY = -minY;
	}
		
	width = maxX + 1 + shiftX;
	height = maxY + 1 + shiftY;
	board.resize(width * height);
    
    fillDead();
}

void GameBoard::fillDead() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            (*this)(x, y) = State::Dead;
        }
    }
}

void GameBoard::fillRandom() {
    width = 95;
    height = 49;

    board.resize(width * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            (*this)(x, y) = (rand() % 4 == 0) ? State::Alive : State::Dead;
        }
    }
}

State& GameBoard::operator()(int x, int y) {
	if (x < 0) 
		x = width + (x % width) - shiftX;
	else 
		x = x % width - shiftX;
		
	if (y < 0) 
		y = height + (y % height) - shiftY;
	else 
		y = y % height - shiftY;
		
	return board[y * width + x];
}

const State& GameBoard::operator()(int x, int y) const {
	if (x < 0) 
		x = width + (x % width) - shiftX;
	else 
		x = x % width - shiftX;
		
	if (y < 0) 
		y = height + (y % height) - shiftY;
	else 
		y = y % height - shiftY;
		
	return board[y * width + x];
}

GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        board = other.board;
    }
    return *this;
}

int GameBoard::getHeight() const {
    return height;
}

int GameBoard::getWidth() const {
    return width;
}

int GameBoard::getMinX() const {
	return -shiftX;
}

int GameBoard::getMinY() const {
	return -shiftY;
}
