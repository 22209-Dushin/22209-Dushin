#include "mix_converter.h"
#include "converter.h"

void mixConverter::convert(int16_t* block, size_t sizeOfBlock, size_t blockBegin) {
    int16_t* mixBlock = new int16_t[sizeOfBlock];
    size_t mixSize = mixingStream.read(mixBlock, sizeOfBlock);
    if ((blockBegin >= end && 0 != end)|| blockBegin<begin)
        return;
    for (size_t i =0; i < sizeOfBlock; ++i) {
        int16_t avg = block[i];
        if (i < mixSize) {
            avg /= 2;
            avg += mixBlock[i] / 2;
        }
        block[i] = avg;
    }
    delete[] mixBlock;
}

std::shared_ptr<converter> mixConverterCreator::parse(
    const std::vector<int>& iargs,
    const std::vector<std::string>& files,
    const std::vector<size_t>& fileIndexes
) const {
    if (iargs.size() > 2 || fileIndexes.size() != 1)
        throw configFailure("Bad arguments for mix converter");
    int beg = iargs.size() >= 1 ? iargs[0] : 0;
    int end = iargs.size() == 2 ? iargs[1] : 0;
    if (beg < 0 || end < 0)
        throw configFailure("Bad arguments for mix converter");
    inputSampleStream iss{ files[fileIndexes[0]] };
    return std::make_shared<mixConverter>(
        iss,
        static_cast<size_t>(beg) * SAMPLE_RATE,
        static_cast<size_t>(end) * SAMPLE_RATE
    );
}

const char* mixConverterCreator::convName() const { 
    return "mix"; 
}

const char* mixConverterCreator::convHelp() const {
    return "mix converter: "
        "Mixes stream from previous converter with input stream\n"
        "configuration: mix $<stream number> <begin>[=0] <end>[=0]\n";
}


