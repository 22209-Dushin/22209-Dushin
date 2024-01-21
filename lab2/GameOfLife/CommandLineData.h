#ifndef COMMANDLINEDATA_H
#define COMMANDLINEDATA_H

#include <string>

struct ComandLineData {
    std::string inFile;
    std::string outFile;
    int iterations = 1;
};

#endif
