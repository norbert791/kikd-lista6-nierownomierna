#include "IdQuantizer.hpp"

signedPixel IdQuantizer::assignQuant(signedPixel pix) {
    return signedPixel{pix.red, pix.green, pix.blue};
}

signedPixel IdQuantizer::getQuantVector(signedPixel pix) {
    return pix;
}

std::vector<signedPixel> IdQuantizer::mapToIndexes(const std::vector<signedPixel>& image) {
    std::vector<signedPixel> result(image.size(), {0,0,0});
    for (size_t i = 0; i < image.size(); i++) {
        result[i] = {image[i].red, image[i].green, image[i].blue};
    }
    return result;
}