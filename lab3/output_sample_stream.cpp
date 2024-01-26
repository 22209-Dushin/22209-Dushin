#include <cstring>
#include "processor.h"
#include "wav_failure.h"
#include "output_sample_stream.h"

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

outputSampleStream::outputSampleStream(const std::string& filename)
    : name(filename), dataSize(0) {
    file.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
    try {
        file.open(filename, std::ios::out | std::ios::binary);
    }
    catch (const std::fstream::failure& e) {
        throw std::fstream::failure("Cannot open input file");
    }
    try {
        file.write(wavHeader, 44);
    }
    catch (const std::fstream::failure& e) {
        throw std::fstream::failure("Unexpected exception while writing output file");
    }
}

void outputSampleStream::write(const int16_t* buffer, size_t size) {
    size *= 2;
    dataSize += size;
    std::streampos tmp = file.tellp();
    commitWavFile();
    tmp = file.tellp();
    char* cbuf = new char[size];
    for (size_t i = 0; i < size / 2; ++i)
        i16__to_le(cbuf + i * 2, buffer[i]);
    file.write(cbuf, size);
    tmp = file.tellp();
    delete[] cbuf;
}

void outputSampleStream::commitWavFile() {
    char buf[4];
    ui32_to_le(buf, dataSize + 36);
    file.seekp(4, file.beg);
    file.write(buf, 4);
    ui32_to_le(buf, dataSize);
    file.seekp(40, file.beg);
    file.write(buf, 4);
    file.seekp(0, file.end);
}


