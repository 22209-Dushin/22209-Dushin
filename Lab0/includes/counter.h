#pragma once

#include <string>
#include <vector>
#include <map>

class Counter {
public:
    void contWords(const std::string fileNAme);
    void sortWords();
    void writeCSV(const std::string fileName);

private:
    std::vector<std::pair<std::string, int>> sortedWords;
    std::map<std::string, int> words;
};


