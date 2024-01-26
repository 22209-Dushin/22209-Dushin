#include <cmath>
#include "volume_converter.h"
#include "converter.h"
#include "config_failure.h"

void volumeConverter::convert(int16_t* block, size_t numberOfBlocks, size_t blockBegin) {
    if ((blockBegin >= end && 0 != end) || blockBegin < begin)
        return;
    double vol = volume;
    vol /= 100;
    for (size_t i =0; i < numberOfBlocks; ++i) {
        double newValue = block[i];
        newValue *= vol;
        if (block[i] < 0)
            block[i] = (newValue >= INT16_MIN) ? static_cast<int16_t>(newValue) : INT16_MIN;
        else
            block[i] = (newValue <= INT16_MAX) ? static_cast<int16_t>(newValue) : INT16_MAX;
    }
}

std::shared_ptr<converter> volumeConverterCreator::parse(
    const std::vector<int>& iargs,
    const std::vector<std::string>& files,
    const std::vector<size_t>& fileIndexes
) const {
    if (iargs.size() < 1 || iargs.size() > 3 || fileIndexes.size() != 0)
        throw configFailure("Bad number of arguments for volume converter");
    int vol = iargs[0];
    int beg = iargs.size() >= 2 ? iargs[1] : 0;
    int end = iargs.size() == 3 ? iargs[2] : 0;
    if (beg < 0 || end < 0)
        throw configFailure("Bad arguments for volume converter");
    return std::make_shared<volumeConverter>(
        static_cast<size_t>(vol),
        static_cast<size_t>(beg) * SAMPLE_RATE,
        static_cast<size_t>(end) * SAMPLE_RATE
    );
}

const std::string volumeConverterCreator::convHelp() const {
    return "volume converter: "
        "Multiplying samples in interval by a <volume>/100.\n"
        "configuration: vol <volume> <begin>[=0] <end>[=0]\n";
}

const std::string volumeConverterCreator::convName() const { return "vol"; }


