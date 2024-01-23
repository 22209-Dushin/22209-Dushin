#include "Controller.h"
#include "LineParser.h"
#include "FileParser.h"
#include "Command.h"
#include "CommandLineData.h"
#include "CommandData.h"

int main(int argc, char** argv) {
    LineParser lineParser;
    FileParser fileParser;
    ComandLineData clData;
    GameData gameData;

    lineParser.parse(argc, argv, clData);

    fileParser.parse(clData.inFile, gameData);

    Game GameOfLife(gameData);

    View ViewGame(GameOfLife);

    Controller GameController(GameOfLife, ViewGame, clData);

    GameController.start();

    return 0;
}
