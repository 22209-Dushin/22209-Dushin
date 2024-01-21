#include "Game.h"

int Game::countNeighbours(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (board(x + j, y + i) == State::Alive) {
                ++count;
            }
        }
    }
    return count;
}

Game::Game(GameData gameData)
    : name(gameData.name), board(gameData.aliveCells, gameData.maxY, gameData.maxX), lastBoard(gameData.maxY, gameData.maxX) {

    bornRules.resize(9, false);
    surviveRules.resize(9, false);

    auto processRules = [&](char ruleIdentifier, std::vector<bool>& ruleMap) {
        int i = 0;
        while (i < gameData.rules.size()) {
            if (gameData.rules[i] == ruleIdentifier) {
                ++i;
                while (i < gameData.rules.size() && gameData.rules[i] != '/') {
                    int rule = gameData.rules[i] - '0';
                    ruleMap[rule] = true;
                    ++i;
                }
                break;
            }
            ++i;
        }
    };

    processRules('B', bornRules);
    processRules('S', surviveRules);

    if (gameData.aliveCells.empty()) {
        board.fillRandom();
        lastBoard.fillRandom();
    }
}

std::string Game::getName() {
    return name;
}

int Game::getHeight() {
    return board.getHeight();
}

int Game::getWidth() {
    return board.getWidth();
}

std::string Game::getRules() {
    std::string rules;

    rules += "B";
    for (int i = 0; i < 9; ++i) {
        if (bornRules[i]) {
            rules += std::to_string(i);
        }
    }

    rules += "/S";
    for (int i = 0; i < 9; ++i) {
        if (surviveRules[i]) {
            rules += std::to_string(i);
        }
    }
    return rules;
}

void Game::createRandomBoard() {
    board.fillRandom();
}

void Game::updateBoard() {
    lastBoard.fillDead();
    for (int x = 0; x < getWidth(); ++x) {
        for (int y = 0; y < getHeight(); ++y) {
            int neighbours = countNeighbours(x, y);
            if (checkCell(x, y) && surviveRules[neighbours] || (!checkCell(x, y)) && bornRules[neighbours]) {
                lastBoard(x, y) = State::Alive;
            }
        }
    }

    std::swap(board, lastBoard);
}

bool Game::checkCell(int x, int y) {
    return board(x, y) == State::Alive;
}
