#pragma once
#include <fstream>
#include <cstdint>
#include <string>

class outputSampleStream {
public:
    outputSampleStream(const std::string&);
    ~outputSampleStream() {
        file.close();
    }
    void write(const int16_t* buffer, size_t size);
    const std::string&getName() const { 
        return name; 
    }
private:
    std::ofstream file;
    std::size_t dataSize;
    const std::string name;
    void commitWavFile();
};

