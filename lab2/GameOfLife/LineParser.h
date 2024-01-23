#ifndef LINEPARSER_H
#define LINEPARSER_H

#include <string>
#include "CommandLineData.h"

class LineParser {
public:
    void parse(int argc, char** argv, ComandLineData& data);
};

#endif
