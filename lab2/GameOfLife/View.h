#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Game.h"
#include "CommandData.h"
#include "Command.h"


class View {
private:
    Game& game;

public:
    View(Game& model);

    void draw(int currIteration);
    void draw(std::string fileName);
    CommandData checkInput();
    void help();
};

#endif /* VIEW_H */
