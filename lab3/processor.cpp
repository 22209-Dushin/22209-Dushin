#include "processor.h"
#include "config.h"

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


