#include "counter.h"

int main(int argc, char** argv) {
    Counter counter;

    counter.contWords(argv[1]);

    counter.sortWords();

    counter.writeCSV(argv[2]);

    return 0;
}

