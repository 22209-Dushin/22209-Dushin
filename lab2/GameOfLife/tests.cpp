#include <gtest/gtest.h>
#include <functional>
#include <algorithm>
#include "Controller.h"
#include "LineParser.h"
#include "FileParser.h"
#include "Command.h"
#include "CommandLineData.h"
#include "CommandData.h"
#include "GameBoard.h"
#include "Game.h"
#include "GameData.h"
#include "State.h"
#include "Point.h"


using namespace testing;


class FileTest : public Test {
protected:
    void SetUp() override {
        std::ofstream file(testFileName);
        file << "#N TestGame" << std::endl;
        file << "#R B3/S23" << std::endl;
        file << "0 0" << std::endl;
        file << "1 1" << std::endl;
        file.close();
    }

    void TearDown() override {
        std::remove(testFileName.c_str());
    }

    std::string testFileName = "test.txt";
};

TEST_F(FileTest, FileParsingTest) {
    GameData gameData;
    FileParser fileParser;

    fileParser.parse(testFileName, gameData);

    EXPECT_EQ(gameData.name, "TestGame");
    EXPECT_EQ(gameData.rules, "B3/S23");
    EXPECT_EQ(gameData.maxX, 1);
    EXPECT_EQ(gameData.maxY, 1);
}


TEST(GameBoardTest, RandomBoardTest) {
    GameBoard gameBoard(95, 49, 0 , 0);

    gameBoard.fillRandom();

    EXPECT_EQ(gameBoard.getHeight(), 49);
    EXPECT_EQ(gameBoard.getWidth(), 95);
}


TEST(GameTest, RulesTest) {
    GameData gameData;
    gameData.rules = "B1357/S02468";
    gameData.aliveCells = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
    gameData.maxX = 9;
    gameData.maxY = 9;

    Game game(gameData);


    EXPECT_EQ(game.getRules(), "B1357/S02468");
}


TEST(GameTest, UpdateBoardTest) {
    GameData gameData;
    gameData.rules = "B3/S23";
    gameData.aliveCells = { {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2 } }; 
    gameData.maxX = 0;
    gameData.maxY = 2;

    Game game(gameData);

    game.updateBoard();

    std::vector<Point> expectedCells = { {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2} };
    std::sort(expectedCells.begin(), expectedCells.end(), [](const Point& a, const Point& b) {
        return std::tie(a.x, a.y) < std::tie(b.x, b.y);
    });

    std::sort(gameData.aliveCells.begin(), gameData.aliveCells.end(), [](const Point& a, const Point& b) {
        return std::tie(a.x, a.y) < std::tie(b.x, b.y);
    });
	
	for (int i = 0; i < 5; ++i) {
    	EXPECT_TRUE(gameData.aliveCells[i].x == expectedCells[i].x);
    	EXPECT_TRUE(gameData.aliveCells[i].y == expectedCells[i].y);
    }
}



TEST(GameTest, GetName) {
    GameData gameData;
    gameData.name = "Conway's Game of Life";
    Game game(gameData);

    EXPECT_EQ(game.getName(), "Conway's Game of Life");
}

TEST(GameTest, GetRules) {
    GameData gameData;
    gameData.rules = "B3/S23";
    Game game(gameData);

    EXPECT_EQ(game.getRules(), "B3/S23");
}

TEST(GameTest, CheckCell) {
    GameData gameData;
    gameData.maxX = 2;
    gameData.maxY = 2;
    gameData.aliveCells = {{0, 0}, {1, 0}, {2, 1}, {1, 2}};
    Game game(gameData);

    EXPECT_TRUE(game.checkCell(0, 0));
    EXPECT_TRUE(game.checkCell(1, 0));
    EXPECT_TRUE(game.checkCell(2, 1));
    EXPECT_TRUE(game.checkCell(1, 2));
    EXPECT_FALSE(game.checkCell(2, 0));
    EXPECT_FALSE(game.checkCell(-1, 0));
}

TEST(GameTest, CountNeighbours) {
    GameData gameData;

    gameData.aliveCells = {{1, 2}, {2, 2}, {3, 2}};
    gameData.maxX = 3;
    gameData.maxY = 2;
    gameData.minX = 1;
    gameData.minY = 2;

    Game game(gameData);
}

TEST(GameTest, UpdateBoard) {
    GameData gameData;
   
    gameData.aliveCells = {{1, 2}, {2, 2}, {3, 2}};
    gameData.maxX = 3;
    gameData.maxY = 2;
    gameData.minX = 1;
    gameData.minY = 2;
    gameData.rules = "B3/S23";

    Game game(gameData);
    game.updateBoard();

 
    EXPECT_EQ(game.checkCell(1, 2), false);
    EXPECT_EQ(game.checkCell(2, 2), true);
    EXPECT_EQ(game.checkCell(3, 2), false);
}


TEST(FileParserTest, Parse) {
    FileParser fileParser;
    GameData gameData;

   
    std::string inputFile = "game_data.txt";
    int result = fileParser.parse(inputFile, gameData);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(gameData.name, "-----");
    EXPECT_EQ(gameData.rules, "B3/S23");
    EXPECT_EQ(gameData.aliveCells.size(), 0);
    EXPECT_EQ(gameData.maxX, 0);
    EXPECT_EQ(gameData.maxY, 0);
    EXPECT_EQ(gameData.minX, 0);
    EXPECT_EQ(gameData.minY, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

