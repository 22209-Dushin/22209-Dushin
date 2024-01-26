#pragma once
#include <string>
#include <vector>
#include "converter.h"
#include "input_sample_stream.h"
#include "output_sample_stream.h"
#include "config.h"

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
