#pragma once
#include "processor.h"

class volumeConverter : public converter {
public:
    volumeConverter(unsigned int vol, size_t b = 0, size_t e = 0) {
        begin = b;
        end = e; 
        volume = vol;
    }
    void convert(int16_t*, size_t, size_t);
    ~volumeConverter(){}
private:
    unsigned int volume;
    size_t begin;
    size_t end;
};

class volumeConverterCreator : public convectorCreator {
public:
    std::shared_ptr<converter> parse(
        const std::vector<int>& iargs,
        const std::vector<std::string>& streams,
        const std::vector<size_t>& streamIndexes
    ) const;
    const char* convName() const;
    const char* convHelp() const;
};
