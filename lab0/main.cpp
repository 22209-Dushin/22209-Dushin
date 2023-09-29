#include "counter.h"

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Error argc" << std::endl;
		return 0;
	}
	
    Counter counter;

    counter.countWords(argv[1]);

    counter.sortWords();

    counter.writeCSV(argv[2]);

    return 0;
}

