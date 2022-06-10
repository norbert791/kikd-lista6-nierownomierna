#include "UniformFilterQuantizer.hpp"

#include <vector>
#include <algorithm>
#include <cmath>

UniformFilterQuantizer::UniformFilterQuantizer(uint8_t bitsPerPixel) {

    quantVector.reserve(pow(2, bitsPerPixel));

    auto numberOfColors = pow(2, bitsPerPixel);

    int16_t step = 512 / numberOfColors;
    for (int16_t index = -255; index < 256 - step; index += step) {
        quantVector.push_back(index + step / 2);
    }
}

signedPixel UniformFilterQuantizer::assignQuant(signedPixel pixel) {
    auto r = std::lower_bound(quantVector.begin(), quantVector.end(), pixel.red);
    auto g = std::lower_bound(quantVector.begin(), quantVector.end(), pixel.green);
    auto b = std::lower_bound(quantVector.begin(), quantVector.end(), pixel.blue);
    signedPixel result{0,0,0};
    auto fun = [&](auto it) {if (it == quantVector.end()) return *(--it); else return *it;};
    return signedPixel{fun(r), fun(g), fun(b)};
}

signedPixel UniformFilterQuantizer::getQuantVector(signedPixel index) {
    return signedPixel{quantVector[index.red], quantVector[index.green], quantVector[index.blue]};
}

std::vector<signedPixel> UniformFilterQuantizer::mapToIndexes(const std::vector<signedPixel>& image) {
    std::vector<signedPixel> result;
    result.reserve(image.size());
    for (auto& pixel : image) {
        int16_t r = std::find(quantVector.begin(), quantVector.end(), pixel.red) - quantVector.begin();
        int16_t g = std::find(quantVector.begin(), quantVector.end(), pixel.green) - quantVector.begin();
        int16_t b = std::find(quantVector.begin(), quantVector.end(), pixel.blue) - quantVector.begin();
        result.push_back(signedPixel{r, g, b});
    }
    return result;
}
