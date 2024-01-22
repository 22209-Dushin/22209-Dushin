#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Game.h"
#include "View.h"
#include "CommandLineData.h"
#include "Command.h"
#include "CommandData.h"

class Controller {
public:
    Controller(Game& game, View& view, ComandLineData clData);

    void start();

private:
    Game& game;
    View& view;
    std::string outFileName;
    int iterations;

    void offlineMode();
    void onlineMode();
    void tick();
};

#endif
