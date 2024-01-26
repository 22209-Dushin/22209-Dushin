#pragma once
#include <string>
#include <vector>
#include "converter.h"
#include "factory.h"

class Config {
public:
    using converterVector = std::vector<std::shared_ptr<converter>>;
    Config(const std::string&, const std::vector<std::string>&);
    const converterVector& getConverters() const { 
        return converters; }
    const static std::vector<convectorCreator*>& creators;
private:
    converterVector converters;
    Factory factory;
    void readConfig(std::ifstream&, const std::vector<std::string>&);
    std::shared_ptr<converter> converterParser(
        const std::string& name,
        const std::vector<int>& iargs,
        const std::vector<std::string>& streams,
        const std::vector<size_t>& streamIndexes
    );
};
