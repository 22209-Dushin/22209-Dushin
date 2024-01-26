#include <cstring>
#include "wav_failure.h"
#include "input_sample_stream.h"

namespace {
    const char* wavHeader = "RIFF\0\0\0\0WAVE"
        "fmt\x20\x10\0\0\0"     // fmt chunk header
        "\x01\0\x01\0"          // PCM mono
        "\x44\xAC\0\0"          // 44100
        "\x88\x58\x01\0"        // 88200
        "\2\0\x10\0"            // align & bits per sample
        "data\0\0\0\0";         // data chunk header


    uint32_t le_to_ui32(const char bytes[4]) {
        return (bytes[0] & 0xff) | ((bytes[1] & 0xff) << 8) | ((bytes[2] & 0xff) << 16) | ((bytes[3] & 0xff) << 24);
    }

    void ui32_to_le(char bytes[4], uint32_t i) {
        bytes[0] = i & 0xff;
        bytes[1] = (i >> 8) & 0xff;
        bytes[2] = (i >> 16) & 0xff;
        bytes[3] = (i >> 24) & 0xff;
    }

    uint16_t le_to_i16(const char bytes[2]) {
        return (bytes[0] & 0xff) | ((bytes[1] & 0xff) << 8);
    }

    void i16__to_le(char bytes[2], uint16_t i) {
        bytes[0] = i & 0xff;
        bytes[1] = (i >> 8) & 0xff;
    }
}


inputSampleStream::inputSampleStream(const std::string& filename) : name(std::string(filename)) {
    file.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
    try {
        file.open(filename, std::ios::in | std::ios::binary);
    }
    catch (const std::fstream::failure& e) {
        throw std::fstream::failure("Cannot open input file");
    }
    try {
        initWavFile();
    }
    catch (const std::fstream::failure& e) {
        throw wavFailure("Bad input WAV file");
    }
}

size_t inputSampleStream::read(int16_t* buffer, size_t size) {
    size *= 2;
    std::streampos curpos = file.tellg();
    if (size + curpos - dataBegin > bytesOfData)
        size = bytesOfData - (curpos - dataBegin);
    size = (size / 2) * 2;
    char* cbuf = reinterpret_cast<char*>(buffer);
    try {
        file.read(cbuf, size);
    }
    catch (const std::ifstream::failure& e) {
        throw wavFailure("Unexpected failure during reading file.");
    }
    for (size_t i = 0; i < size / 2; ++i) {
        int16_t tmp = le_to_i16(cbuf + i * 2);
        buffer[i] = tmp;
    }
    return size / 2;
}

void inputSampleStream::initWavFile() {
    char buff[4];
    enum { RIFF, SEARCHFMT, FMT, SEARCHDATA, DATA } state = RIFF;
    while (state != DATA) {
        if (state == RIFF) {
            file.read(buff, 4);
            if (0 != strncmp(buff, "RIFF", 4))
                throw wavFailure();
            file.read(buff, 4);
            file.read(buff, 4);
            if (0 != strncmp(buff, "WAVE", 4))
                throw wavFailure();
            state = SEARCHFMT;
        }
        else if (state == SEARCHFMT) {
            file.read(buff, 4);
            if (0 != strncmp(buff, "fmt\x20", 4)) {
                file.read(buff, 4);
                uint32_t subchunkSize = le_to_ui32(buff);
                file.seekg(subchunkSize, file.cur);
                state = SEARCHFMT;
            }
            else {
                state = FMT;
            }
        }
        else if (state == FMT) {
            file.read(buff, 4);
            uint32_t subchunkSize = le_to_ui32(buff);
            file.read(buff, 2);
            if (1 != buff[0] || buff[1] != 0 || 16u != subchunkSize)
                throw wavFailure("Not a PCM format");
            file.read(buff, 2);
            if (1 != buff[0] || 0 != buff[1])
                throw wavFailure("Not a mono");
            file.read(buff, 4);
            if (SAMPLE_RATE != le_to_ui32(buff))
                throw wavFailure("Not a 44100 rate");
            file.seekg(8, file.cur);
            state = SEARCHDATA;
        }
        else if (state == SEARCHDATA) {
            file.read(buff, 4);
            if (0 != strncmp(buff, "data", 4)) {
                file.read(buff, 4);
                uint32_t subchunkSize = le_to_ui32(buff);
                file.seekg(subchunkSize, file.cur);
                state = SEARCHDATA;
            }
            else {
                file.read(buff, 4);
                dataBegin = file.tellg();
                bytesOfData = le_to_ui32(buff);
                state = DATA;
            }
        }
    }
}
