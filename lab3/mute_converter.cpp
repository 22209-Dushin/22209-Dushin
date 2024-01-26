#include "mute_converter.h"
#include "converter.h"
#include "config_failure.h"

void muteConverter::convert(int16_t* block, size_t sizeOfBlock, size_t blockBegin) {
    if ((blockBegin >= end && 0 != end) || blockBegin < begin)
        return;
    for (size_t i =0; i < sizeOfBlock; ++i)
        block[i] = 0;
}

std::shared_ptr<converter> muteConverterCreator::parse(
    const std::vector<int>& iargs,
    const std::vector<std::string>& files,
    const std::vector<size_t>& fileIndexes
) const {
    if (iargs.size() > 2 || fileIndexes.size() != 0)
         throw configFailure("Bad number of arguments for mute converter");
    int beg = iargs.size() >= 1 ? iargs[0] : 0;
    int end = iargs.size() == 2 ? iargs[1] : 0;
    if (beg < 0 || end < 0)
        throw configFailure("Bad arguments for mute converter");
    return std::make_shared<muteConverter>(
        static_cast<size_t>(beg) * SAMPLE_RATE,
        static_cast<size_t>(end) * SAMPLE_RATE
    );
}

const std::string muteConverterCreator::convHelp() const {
    return "mute converter: "
        "Mutes stream from previous converter at interval\n"
        "configuration: mute <begin>[=0] <end>[=0]\n";
}

const std::string muteConverterCreator::convName() const { return "mute"; }


