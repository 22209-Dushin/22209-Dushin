#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdint>
#include "processor.h"
#include "wav_failure.h"

void getArguments(std::string& out, std::string& config, std::vector<std::string>& in, int argc, char* argv[]) {
    unsigned int argi = 1;
    enum class State{ FIRST, CONF, OUT, IN };
    State state = State::FIRST;
    while (argi < argc) {
        switch (state) {
            case State::FIRST:
                if (0 == strcmp("-c", argv[argi])) {
                    config = argv[++argi];
                    state = State::OUT;
                }
                else {
                    out = argv[argi];
                    state = State::CONF;
                }
                break;

            case State::CONF:
                if (0 == strcmp("-c", argv[argi])) {
                    config = argv[++argi];
                    state = State::IN;
                }
                else {
                    in.push_back(argv[argi]);
                    state = State::CONF;
                }
                break;

            case State::OUT:
                out = argv[argi];
                state = State::IN;
                break;

            case State::IN:
                in.push_back(argv[argi]);
                state = State::IN;
                break;
        }
        ++argi;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && 0 == strcmp(argv[1], "-h")) {
        std::cout << "sound_processor [-h] "
            "[-c config.txt "
            "output.wav input1.wav [input2.wav ...]]\n" << std::endl;
        std::cout << "Valid input files are WAV files; mono PCM s16le 44100Hz format.\n" << std::endl;
        std::cout << "Converters:\n" << std::endl;
        for (auto creator : Config::creators)
            std::cout << creator->convHelp() << std::endl;
        return 0;
    }
    std::string out;
    std::string conf;
    std::vector<std::string> input;
    getArguments(out, conf, input, argc, argv);
    if (out.compare("") == 0) {
        std::cerr << "No output file!" << std::endl;
        return 1;
    }
    if (conf.compare("") == 0) {
        std::cerr << "Configuration file is required!" << std::endl;
        return 1;
    }
    if (0 == input.size()) {
        std::cerr << "No input files!" << std::endl;
        return 1;
    }

    try {
        Config configuration{ conf, input };
        processor proc{ configuration, out, input[0] };
        proc.run();
    }
    catch (const wavFailure& e) {
        std::cerr << e.what() << std::endl;
        return 3;
    }
    catch (const std::fstream::failure& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
