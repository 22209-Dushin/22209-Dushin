#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include "Command.h"

struct CommandData {
	Command command;
	int iterations = 1;
	std::string outFile;
};

#endif
