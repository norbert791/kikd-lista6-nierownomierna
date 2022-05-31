#ifndef CODER_HPP
#define CODER_HPP

#include <vector>
#include "image.h"

class Coder {
    public:
        virtual std::vector<signedPixel> encode(const std::vector<signedPixel>& image) = 0;
        virtual std::vector<signedPixel> decode(const std::vector<signedPixel>& image) = 0;
        virtual ~Coder() = default;
};


#endif