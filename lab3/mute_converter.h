#pragma once
#include "processor.h"

class muteConverter : public converter {
public:
    muteConverter(size_t b = 0, size_t e = 0) : begin(b), end(e) {  }
    void convert(int16_t*, size_t, size_t);
    ~muteConverter() noexcept {}
private:
    size_t begin;
    size_t end;
};

class muteConverterCreator : public convectorCreator {
public:
    std::shared_ptr<converter> parse(
        const std::vector<int>& iargs,
        const std::vector<std::string>& streams,
        const std::vector<size_t>& streamIdxs
    ) const;
    const char* convName() const;
    const char* convHelp() const;
};


