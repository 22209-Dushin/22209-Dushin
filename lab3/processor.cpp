#include <fstream>
#include <sstream>
#include "processor.h"
#include "mute_converter.h"
#include "mix_converter.h"
#include "volume_converter.h"

namespace {
    muteConverterCreator mucc;
    mixConverterCreator micc;
    volumeConverterCreator vcc;
    const std::vector<convectorCreator*> USABLE_CONVERTERS = {
        &mucc,
        &micc,
        &vcc
    };
}

std::shared_ptr<converter> Config::converterParser(
    const std::string& name,
    const std::vector<int>& iargs,
    const std::vector<std::string>& streams,
    const std::vector<size_t>& streamIndexes
) {
    for (auto creator : creators) {
    	if (0 == name.compare(creator->convName()))
            return creator->parse(iargs, streams, streamIndexes);
    }
    throw configFailure("Bad converter name");
}

const std::vector<convectorCreator*>& Config::creators = USABLE_CONVERTERS;

Config::Config(const std::string& filename, const std::vector<std::string>& streams) {
    std::ifstream f;
    f.exceptions(std::fstream::badbit | std::fstream::failbit);
    try {
        f.open(filename, std::ios::in);
    }
    catch (const std::fstream::failure& e) {
        throw std::fstream::failure("Cannot open configuration file");
    }
    try {
        readConfig(f, streams);
    }
    catch (const std::fstream::failure& e) {
        throw std::fstream::failure("Unexpected failure during reading configuration file");
    }
}

void Config::readConfig(std::ifstream& f, const std::vector<std::string>& streams) {
    while (!f.eof() && EOF != f.peek()) {
        std::stringstream ss;
        std::string name;
        getline(f, name);
        ss << name;
        ss >> name;
        if ('#' == name[0])
            continue;
        std::vector<int> iargs;
        std::vector<size_t> inIndexes;
        std::string buf;
        while (!ss.eof()) {
            ss >> buf;
            if (buf[0] == '$') {
                buf.erase(0, 1);
                size_t id = 0;
                try {
                    id = std::stoul(buf);
                }
                catch (const std::exception&) {
                    throw configFailure("Bad stream number after $");
                }
                if (id >= streams.size() + 1 || 0 == id)
                    throw configFailure("Bad stream number after $");
                inIndexes.push_back(id - 1);
            }
            else if (!buf.empty()) {
                try {
                    iargs.push_back(std::stoi(buf));
                }
                catch (const std::exception&) {
                    throw configFailure("Bad not integer argument for converter");
                }
            }
        }
        if (!isspace(name[0]))
            converters.push_back(converterParser(name, iargs, streams, inIndexes));
    }
}

void processor::run() {
    size_t size;
    size_t i = 0;
    int16_t output[SAMPLE_RATE];
    const Config::converterVector& converters = config.getConverters();
    while (0 != (size = iss.read(output, SAMPLE_RATE)))
    {
        for (auto converter : converters)
            converter->convert(output, size, i);
        oss.write(output, size);
        i += size;
    }
}


