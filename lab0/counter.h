#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Counter {
public:
    void countWords(const std::string fileNAme);
    void sortWords();
    void writeCSV(const std::string fileName);

private:
    std::vector<std::pair<std::string, int>> sortedWords;
    std::map<std::string, int> words;
};


