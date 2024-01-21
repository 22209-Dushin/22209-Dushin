#ifndef LINEPARSER_H
#define LINEPARSER_H

#include <getopt.h>
#include <string>
#include "CommandLineData.h"

class LineParser {
public:
    void parse(int argc, char** argv, ComandLineData& data);
};

#endif
