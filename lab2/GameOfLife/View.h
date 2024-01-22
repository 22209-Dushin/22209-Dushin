#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include "CommandData.h"



class View {
private:
    const Game& game;

public:
    View(Game& model);

    void draw(int currIteration);
    void draw(std::string fileName);
    CommandData checkInput();
    void help();
};

#endif
