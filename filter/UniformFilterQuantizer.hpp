#ifndef UNIFORM_FILTER_QUANTIZER_HPP
#define UNIFORM_FILTER_QUANTIZER_HPP

#include <vector>
#include <unordered_map>
#include "FilterQuantizer.hpp"

class UniformFilterQuantizer : public FilterQuantizer {

    public:
        UniformFilterQuantizer(uint8_t bitsPerPixel);
        std::vector<signedPixel> mapToIndexes(const std::vector<signedPixel>& image) override;
        signedPixel assignQuant(signedPixel pixel) override;
        signedPixel getQuantVector(signedPixel index) override;
        ~UniformFilterQuantizer() override = default;
    private:
        std::vector<int16_t> quantVector;
        std::unordered_map<int16_t, int16_t> lookup;
        uint8_t bitsPerPixel;
};

#endif