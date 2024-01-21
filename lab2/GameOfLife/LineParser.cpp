#include "LineParser.h"

void LineParser::parse(int argc, char** argv, ComandLineData& data) {
    int option;

    const char* shortOptions = "i:o:";

    const struct option longOptions[] = {
        {"iterations", required_argument, nullptr, 'i'},
        {"output", required_argument, nullptr, 'o'},
        {nullptr, 0, nullptr, 0}
    };

    while ((option = getopt_long(argc, argv, shortOptions, longOptions, nullptr)) != -1) {
        switch (option) {
            case 'i':
                data.iterations = atoi(optarg);
                break;
            case 'o':
                data.outFile = optarg;
                break;
        }
    }

    if (optind < argc)
        data.inFile = argv[optind];
}
