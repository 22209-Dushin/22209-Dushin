#pragma once
#include <cstdint>
#include <cstddef>
#include <memory>
#include "sample_stream.h"

class converter {
public:
    virtual void convert(int16_t*, size_t, size_t) = 0;
    virtual ~converter() {}
};

class convectorCreator {
public:
    virtual std::shared_ptr<converter> parse(const std::vector<int>& iargs, const std::vector<std::string>& streams, const std::vector<size_t>& stream_indexes) const = 0;
    virtual const char* convName() const = 0;
    virtual const char* convHelp() const = 0;
};


