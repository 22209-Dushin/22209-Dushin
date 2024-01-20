#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <unistd.h>

struct ComandLineData {
	std::string inFile;
	std::string outFile;
	int iterations = 1;
};

struct GameData {
	std::string name = "-----";
	std::string rules = "B3/S23";
	std::vector <std::pair<int, int>> aliveCells;
	int maxX = 0;
	int maxY = 0;
};

class LineParser {
public:
	void parse(int argc, char** argv, ComandLineData& clData) {
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg == "-i" || arg == "--iterations") {
				clData.iterations = std::stoi(argv[++i]);
			}
			else if (arg == "-o" || arg == "--output") {
				clData.outFile = argv[++i];
			}
			else {
				clData.inFile = argv[i];
			}
		}
	}
};

class FileParser {
public:
	void parse(std::string inFileName, GameData& gameData) {
		if (inFileName.empty())
			return;

		std::ifstream file(inFileName);
		std::string line;

		while (std::getline(file, line)) {
			if (line[0] == '#') {
				std::stringstream ss(line.substr(1));
				char type;
				ss >> type;

				switch (type) {
				case 'N':
					ss >> gameData.name;
					break;
				case 'R':
					ss >> gameData.rules;
					break;
				}
			}
			else {
				std::stringstream ss(line);
				int x, y;
				ss >> x >> y;
				gameData.aliveCells.push_back({ x, y });
				gameData.maxX = std::max(x, gameData.maxX);
				gameData.maxY = std::max(y, gameData.maxY);
			}
		}
	}
};

class Cell {
private:
	bool alive;

public:
	Cell() : alive(false) {}

	bool isAlive() { return alive; }

	void setAlive(bool state) { alive = state; }
};

class GameBoard {
private:
	int width;
	int height;
	std::vector<Cell> board;

public:
	GameBoard(std::vector<std::pair<int, int>> coordinates, int maxY, int maxX)
		: width(maxX + 1), height(maxY + 1) , board((maxX + 1) * (maxY + 1)) {
		
		if(coordinates.empty()) {
			fillRandom();
		}
		
		else {
			for (const auto& coord : coordinates) {				
				int x = coord.first;
				int y = coord.second;
				board[y * width + x].setAlive(true);
			}	
		}
	}
	GameBoard(int maxX, int maxY) : width(maxX), height(maxY), board(maxX * maxY) {}

	void fillRandom() {
		width = 95;
		height = 49;
		
		board.resize(width * height);

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				board[y * width + x].setAlive(rand() % 4 == 0);
			}
		}
	}
	Cell& operator()(int x, int y) { return board[y * width + x]; }
	GameBoard& operator=(const GameBoard& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            board = other.board;
        }
        return *this;
    }
	int getHeight() { return height; }
	int getWidth() { return width; }
};

class Game {
private:
	std::vector<bool> bornRules = { false, false, false, false, false, false, false, false, false };
	std::vector<bool> surviveRules = {false, false, false, false, false, false, false, false, false };

	int countNeighborns(int x, int y) {
		int count = 0;
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (i == 0 && j == 0) {
					continue;
				}
				if (board((x + j + getWidth()) % getWidth(), (y + i + getHeight()) % getHeight()).isAlive()) {
					++count;
				}
			}
		}
		return count;
	}

public:
	std::string name;
	GameBoard board;
	Game(GameData gameData) : board(gameData.aliveCells, gameData.maxY, gameData.maxX), name(gameData.name) {
		
		for (int i = 0; i < gameData.rules.size(); ++i) {
			if (gameData.rules[i] == 'B') {
				++i;
				while (gameData.rules[i] != '/') {
					int rule = gameData.rules[i] - '0';
					bornRules[rule] = true;
					++i;
				}
			}
			else if (gameData.rules[i] == 'S') {
				++i;
				while (i < gameData.rules.size()) {
					int rule = gameData.rules[i] - '0';
					surviveRules[rule] = true;
					++i;
				}
			}
		}
	}

	int getHeight() { return board.getHeight(); }

	int getWidth() { return board.getWidth(); }

	std::string getRules() {
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

	void createRandomBoard() {
		board.fillRandom();
	}

	void updateBoard() {
		GameBoard newBoard(board.getWidth(), board.getHeight());
		for (int x = 0; x < board.getWidth(); ++x) {
			for (int y = 0; y < board.getHeight(); ++y) {
				int neighborns = countNeighborns(x, y);
			    if (board(x, y).isAlive()) {
					if (surviveRules[neighborns]) {
						newBoard(x, y).setAlive(true);	
					}
				}
				else if (bornRules[neighborns]) {
					newBoard(x, y).setAlive(true);
				}
			}
		}
		board = newBoard;
	}

	bool checkCell(int x, int y) {
		return board(x, y).isAlive();
	}
};

class View {
private:
	Game& game;
public:
	View(Game& model) : game(model) {}

	void draw(int n) {
		sleep(1);
		
		std::cout << "Name : " << game.name << std::endl;
		std::cout << "Rules: " << game.getRules() << std::endl;
		std::cout << "Current iteraion: " << n << std::endl;
		
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

	void draw(std::string fileName) {
		std::ofstream file(fileName);

		file << "#N " << game.name << std::endl;
		file << "#R " << game.getRules() << std::endl;

		for (int y = 0; y < game.getHeight(); ++y) {
			for (int x = 0; x < game.getWidth(); ++x) {
				if (game.checkCell(x, y))
					file << x << ' ' << y << std::endl;
			}
		}
	}
};

class Controller {
public:
	Controller(Game& game, View& view, ComandLineData clData) : game(game), view(view), outFileName(clData.outFile), iterations(clData.iterations) {
		if (clData.inFile.empty())
			game.createRandomBoard();
	}
	void start() {
		if (outFileName.empty())
			onlineMode();
		else
			offlineMode();
	}
private:
	Game& game;
	View& view;
	std::string outFileName;
	int iterations;

	std::string checkInput() {
		std::string line;
		std::string currCommand;
		
		std::getline(std::cin, line);
		std::stringstream ss(line);
		ss >> currCommand;

		if (currCommand == "exit")
			return currCommand;

		else if (currCommand == "help")
			return currCommand;

		else if (currCommand == "tick" || currCommand == "t") {
			ss >> iterations;
			return currCommand;
		}

		else if (currCommand == "dump") {
			ss >> outFileName;
			return currCommand;
		}

		else
			return "help";

	}

	void offlineMode() {
		for (int i = 0; i < iterations; ++i) {
			game.updateBoard();
		}
		
		view.draw(outFileName);
	}
	void onlineMode() {
		std::string currCommand;

		while (true) {
			currCommand = checkInput();

			if (currCommand == "dump") 
				view.draw(outFileName);
			else if (currCommand == "tick") {
				tick();
			}
			else if (currCommand == "exit") {
				break;
			}
			else if (currCommand == "help") {
				help();
			}
		} 
	}
	void tick() {
		for (int i = 1; i <= iterations; ++i) {
			game.updateBoard();
			view.draw(i);
		}
	}
	void help() {
		std::cout << "Chose one of the commands:" << std::endl;
		std::cout << "  dump <filename> - save the universe to file" << std::endl;
		std::cout << "  tick <n=1> (t <n=1>) - calculate n iterations and print the result" << std::endl;
		std::cout << "  exit - finish the game" << std::endl;
	}
};

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
