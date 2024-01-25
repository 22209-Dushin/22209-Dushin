#pragma once
#include "processor.h"

class mixConverter : public converter {
public:
    mixConverter(const inputSampleStream& mixing, size_t b = 0, size_t e = 0)
        : begin(b), end(e),
        mixingStream(mixing){}
    void convert(int16_t*, size_t, size_t);
    ~mixConverter() noexcept {}
private:
    size_t begin;
    size_t end;
    inputSampleStream mixingStream;
};

class mixConverterCreator : public convectorCreator {
    std::shared_ptr<converter> parse(
        const std::vector<int>& iargs,
        const std::vector<std::string>& streams,
        const std::vector<size_t>& stream_indexes
    ) const;
    const char* convName() const;
    const char* convHelp() const;
};

