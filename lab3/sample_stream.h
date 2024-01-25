#pragma once
#include <fstream>
#include <cstdint>
#include <string>

class wavFailure : public std::exception {
public:
    wavFailure(const char* massage) {
        m = massage;
    }
    wavFailure() {
        m = nullptr;
    }
    virtual const char* what() const noexcept{
        if(m == nullptr)
            return "Bad WAV format";
        else
            return m;
    }
private:
    const char* m;
};

class inputSampleStream {
public:
    inputSampleStream(const std::string&);
    inputSampleStream(const inputSampleStream& o) : inputSampleStream(*o.name) {}
    inputSampleStream(inputSampleStream&& o) noexcept : inputSampleStream(*o.name) {}
    ~inputSampleStream() {
        file.close();
        delete name;
    }
    size_t read(int16_t* buffer, size_t size);
    const std::string& getName() const { 
        return *name; 
    }
private:
    std::ifstream file;
    std::streampos dataBegin;
    std::size_t bytesOfData;
    const std::string* name;
    void initWavFile();
};

class outputSampleStream {
public:
    outputSampleStream(const std::string&);
    ~outputSampleStream() {
        file.close();
        delete name;
    }
    void write(const int16_t* buffer, size_t size);
    const std::string& getName() const { 
        return *name; 
    }
private:
    std::ofstream file;
    std::size_t dataSize;
    const std::string* name;
    void commitWavFile();
};


