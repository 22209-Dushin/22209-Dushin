#include "GameBoard.h"
#include <cstdlib>

GameBoard::GameBoard(std::vector<Point> coordinates, int maxY, int maxX)
    : width(maxX + 1), height(maxY + 1), board((maxX + 1) * (maxY + 1)) {

    fillDead();

    for (const auto& coord : coordinates) {
        int x = coord.x;
        int y = coord.y;
        (*this)(x, y) = State::Alive;
    }
}

GameBoard::GameBoard(int maxY, int maxX)
    : width(maxX + 1), height(maxY + 1), board((maxX + 1) * (maxY + 1)) {
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
    return board[(y + getHeight()) % getHeight() * width + (x + getWidth()) % getWidth()];
}

GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        board = other.board;
    }
    return *this;
}

int GameBoard::getHeight() {
    return height;
}

int GameBoard::getWidth() {
    return width;
}
