#ifndef DIFFERENTIAL_CODER_HPP
#define DIFFERENTIAL_CODER_HPP

#include "Coder.hpp"
#include <vector>

class DifferentialCoder : public Coder{
    public:
        std::vector<signedPixel> encode(const std::vector<signedPixel>& image) override;
        std::vector<signedPixel> decode(const std::vector<signedPixel>& image) override;
};

#endif