#include "View.h"
#include <unistd.h>
#include "Command.h"

View::View(Game& model) : game(model) {}

void View::draw(int currIteration) {
    sleep(1);

    std::cout << "Name: " << game.getName() << std::endl;
    std::cout << "Rules: " << game.getRules() << std::endl;
    std::cout << "Current iteration: " << currIteration << std::endl;

    std::cout << ' ';
    for (int i = 0; i < game.getWidth(); i++) {
        std::cout << '_';
    }
    std::cout << std::endl;

    for (int y = game.getHeight() - 1; y >= 0; --y) {
        std::cout << '|';
        for (int x = 0; x < game.getWidth(); ++x) {
            if (game.checkCell(x, y))
                std::cout << "\033[1;32m" << 'O' << "\033[0m";
            else
                std::cout << ' ';
        }
        std::cout << '|' << std::endl;
    }

    std::cout << ' ';
    for (int i = 0; i < game.getWidth(); i++) {
        std::cout << '_';
    }
    std::cout << std::endl;
}

void View::draw(std::string fileName) {
    std::ofstream file(fileName);

    file << "#N " << game.getName() << std::endl;
    file << "#R " << game.getRules() << std::endl;

    for (int y = 0; y < game.getHeight(); ++y) {
        for (int x = 0; x < game.getWidth(); ++x) {
            if (game.checkCell(x, y))
                file << x << ' ' << y << std::endl;
        }
    }
}

CommandData View::checkInput() {
    CommandData cmData;
    std::string line;
    std::string currCommand;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss >> currCommand;

    if (currCommand == "exit")
        cmData.command = Command::exit;
    else if (currCommand == "help")
        cmData.command = Command::help;
    else if (currCommand == "tick" || currCommand == "t") {
        ss >> cmData.iterations;
        cmData.command = Command::tick;
    } else if (currCommand == "dump") {
        ss >> cmData.outFile;
        cmData.command = Command::dump;
    } else {
        cmData.command = Command::help;
    }

    return cmData;
}

void View::help() {
    std::cout << "Choose one of the commands:" << std::endl;
    std::cout << "  dump <filename> - save the universe to a file" << std::endl;
    std::cout << "  tick <n=1> (t <n=1>) - calculate n iterations and print the result" << std::endl;
    std::cout << "  exit - finish the game" << std::endl;
}
