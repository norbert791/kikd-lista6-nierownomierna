#ifndef QUANTIZER_HPP
#define QUANTIZER_HPP

#include <vector>
#include "image.h"

class Quantizer {
    public:
        virtual std::vector<signedPixel> encode(const std::vector<signedPixel>& image, uint8_t bitsPerPixel) = 0;
        virtual std::vector<signedPixel> decode(const std::vector<signedPixel>& image) = 0;
        virtual ~Quantizer() = default;
};


#endif