#include "UniformFilterQuantizer.hpp"

#include <vector>
#include <algorithm>
#include <cmath>

UniformFilterQuantizer::UniformFilterQuantizer(uint8_t bitsPerPixel) {

    quantVector.reserve(pow(2, bitsPerPixel));

    auto numberOfColors = pow(2, bitsPerPixel);

    int16_t step = 512 / numberOfColors;
    for (int16_t index = -255; index < 256; index += step) {
        quantVector.push_back(index + step / 2);
        for (int16_t j = index; j < index + step; j++) {
            lookup[j] = index;
        }
    }
}

signedPixel UniformFilterQuantizer::assignQuant(signedPixel pixel) {
 
    signedPixel temp = {lookup[pixel.red], lookup[pixel.green], lookup[pixel.blue]};
    return {quantVector[temp.red], quantVector[temp.green], quantVector[temp.blue]};
}

signedPixel UniformFilterQuantizer::getQuantVector(signedPixel index) {
    return signedPixel{quantVector[index.red], quantVector[index.green], quantVector[index.blue]};
}

std::vector<signedPixel> UniformFilterQuantizer::mapToIndexes(const std::vector<signedPixel>& image) {
    std::vector<signedPixel> result;
    result.reserve(image.size());
    for (auto& pixel : image) {
        result.push_back(signedPixel{lookup[pixel.red], lookup[pixel.green], lookup[pixel.blue]});
    }
    return result;
}
