#ifndef NON_UNIFORM_QUANTIZER_HPP
#define NON_UNIFORM_QUANTIZER_HPP

#include <functional>
#include "Quantizer.hpp"

class NonUniformQuantizer : public Quantizer{
    public:
        std::vector<signedPixel> encode(const std::vector<signedPixel>& image, uint8_t bitsPerPixel) override;
        std::vector<signedPixel> decode(const std::vector<signedPixel>& image) override;

    private:
        std::vector<int16_t> quantize(const std::vector<signedPixel>& image, std::function<int16_t(signedPixel)> cast, uint8_t bits);
};

#endif