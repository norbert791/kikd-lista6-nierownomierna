#include <iostream>
#include "LowerFilter.hpp"


std::vector<signedPixel> LowerFilter::applyFilter(const std::vector<pixel>& image) {

    if (image.size() == 0) {
        std::vector<signedPixel> temp;
        return temp;
    }
    
    std::vector<signedPixel> result(image.size(), {0,0,0});

    result[0] = image[0];

    for (size_t i = 1; i < image.size(); i++) {
        result[i].red = meanValue(image[i - 1].red, image[i].red);
        result[i].green = meanValue(image[i - 1].green, image[i].green);
        result[i].blue = meanValue(image[i - 1].blue, image[i].blue);
    }

    return result;
}

std::vector<pixel> LowerFilter::removeFilter(const std::vector<signedPixel>& filteredImage) {

    if (filteredImage.size() == 0) {
        std::vector<pixel> temp;
        return temp;
    }

    std::vector<pixel> result(filteredImage.size(), {0,0,0});

    result[0].red = filteredImage[0].red;
    result[0].green = filteredImage[0].green;
    result[0].blue = filteredImage[0].blue;

    for (size_t i = 1; i < filteredImage.size(); i++) {
        result[i].red = (uint8_t) ((uint16_t)(filteredImage[i]).red * 2 - result[i - 1].red);
        result[i].green = (uint8_t) ((uint16_t)(filteredImage[i]).green * 2 - result[i - 1].green);
        result[i].blue = (uint8_t) ((uint16_t)(filteredImage[i]).blue * 2 - result[i - 1].blue);
    }

    return result;
}

inline uint8_t LowerFilter::meanValue(uint8_t num1, uint8_t num2) const {
    return num1 / 2 + num2 / 2 + (num1 & num2 & 1);
} 