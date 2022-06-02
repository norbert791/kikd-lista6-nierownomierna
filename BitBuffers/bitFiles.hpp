#ifndef BIT_FILES_HPP
#define BIT_FILES_HPP

#include <vector>
#include "image.h"
#include "BitWriter.hpp"
#include "BitReader.hpp"

class BitFiles {

    public:
        void persistImage(const char* fileName, uint8_t bitsPerPixel,
                          uint64_t uncompressedSize, const std::vector<pixel>& pixels);
        std::vector<pixel> retrieveImage(const char* fileName);
};

#endif