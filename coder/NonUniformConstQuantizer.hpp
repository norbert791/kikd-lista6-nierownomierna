#ifndef NON_UNIFORM_CONST_QUANTIZER_HPP
#define NON_UNIFORM_CONST_QUANTIZER_HPP

#include <unordered_map>
#include <vector>
#include "Quantizer.hpp"

class NonUniformConstQuantizer : public Quantizer {
    public:
        NonUniformConstQuantizer(uint8_t bitsPerPixel);
        std::vector<signedPixel> encode(const std::vector<signedPixel>& image, uint8_t bitsPerPixel) override;
        std::vector<signedPixel> decode(const std::vector<signedPixel>& image) override;
    private:
        std::unordered_map<int16_t,int16_t> generateMap(uint8_t bitsPerPixel);
        std::vector<int16_t> generateQuants(uint8_t bitsPerPixel);
        uint8_t levels;
};


#endif