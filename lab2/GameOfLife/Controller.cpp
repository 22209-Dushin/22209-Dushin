#include "Controller.h"
#include "Command.h"

Controller::Controller(Game& game, View& view, ComandLineData clData)
    : game(game), view(view), outFileName(clData.outFile), iterations(clData.iterations) {
    if (clData.inFile.empty())
        game.createRandomBoard();
}

void Controller::start() {
    if (outFileName.empty())
        onlineMode();
    else
        offlineMode();
}

void Controller::offlineMode() {
    for (int i = 0; i < iterations; ++i) {
        game.updateBoard();
    }

    view.draw(outFileName);
}

void Controller::onlineMode() {
    CommandData cmData;
    while (true) {
        cmData = view.checkInput();
        switch (cmData.command) {
            case Command::exit:
                return;
            case Command::help:
                view.help();
                break;
            case Command::tick:
                iterations = cmData.iterations;
                tick();
                break;
            case Command::dump:
                outFileName = cmData.outFile;
                break;
        }
    }
}

void Controller::tick() {
    for (int i = 1; i <= iterations; ++i) {
        game.updateBoard();
        view.draw(i);
    }
}
