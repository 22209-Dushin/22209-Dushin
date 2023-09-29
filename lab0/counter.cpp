#include "counter.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <numeric>

void Counter::countWords(const std::string fileName) {
    std::ifstream file(fileName);

    std::string line;
    while (std::getline(file, line)) {
        for (char& c : line) {
            if (!std::isalnum(c)) {
                c = ' ';
            } else {
                c = std::tolower(c);
            }
        }

        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            ++words[word];
        }
    }
}

void Counter::sortWords() {
    for (const auto& pair : words) {
        sortedWords.push_back(pair);
    }

    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const auto left, const auto right)
        { return left.second > right.second; });
}

void Counter::writeCSV(const std::string fileName) {
    std::ofstream file(fileName);

    int countAllWords = std::accumulate(sortedWords.begin(), sortedWords.end(), 0,
        [](int accumulator, const std::pair<std::string, int>& pair)
        { return accumulator + pair.second; });

    file << "Word,Frequency,Frequency(%)" << std::endl;

    for (const auto& pair : sortedWords) {
        file << pair.first << "," << pair.second << "," << static_cast<double>(pair.second) / countAllWords * 100 << std::endl;
    }
}

