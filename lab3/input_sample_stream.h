#pragma once
#include <fstream>
#include <cstdint>
#include <string>

const size_t SAMPLE_RATE = 44100ul;

class inputSampleStream {
public:
    inputSampleStream(const std::string&);
    inputSampleStream(const inputSampleStream& o) : inputSampleStream(o.name) {}
    inputSampleStream(inputSampleStream&& o) noexcept : inputSampleStream(o.name) {}
    ~inputSampleStream() {
        file.close();
    }
    size_t read(int16_t* buffer, size_t size);
    const std::string getName() const { 
        return name; 
    }
private:
    std::ifstream file;
    std::streampos dataBegin;
    std::size_t bytesOfData;
    const std::string name;
    void initWavFile();
};

