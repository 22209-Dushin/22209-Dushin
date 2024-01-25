#pragma once
#include <string>
#include <vector>
#include "converter.h"
#include "sample_stream.h"

const size_t SAMPLE_RATE = 44100ul;
class configFailure : public std::exception {
public:
    configFailure(const char* massage) {
        m = massage;
    }
    configFailure() {
        m = nullptr; 
    }
    const char* what() const noexcept {
        if (m == nullptr)
            return "Bad configuration file";
        else 
            return m;
    }
private:
    const char* m;
};

class Config {
public:
    using converterVector = std::vector<std::shared_ptr<converter>>;
    Config(const std::string&, const std::vector<std::string>&);
    const converterVector& getConverters() const { 
        return converters; }
    const static std::vector<convectorCreator*>& creators;
private:
    converterVector converters;
    void readConfig(std::ifstream&, const std::vector<std::string>&);
    std::shared_ptr<converter> converterParser(
        const std::string& name,
        const std::vector<int>& iargs,
        const std::vector<std::string>& streams,
        const std::vector<size_t>& streamIndexes
    );
};

class processor {
public:
    processor(const Config& conf, const std::string& output, const std::string& input)
        : config(conf), iss(input), oss(output) {  }
    void run();
private:
    const Config& config;
    inputSampleStream iss;
    outputSampleStream oss;
};

