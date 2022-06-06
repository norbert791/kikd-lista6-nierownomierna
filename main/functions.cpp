#include "functions.hpp"

std::vector<signedPixel> mergeMapping(const std::vector<signedPixel>& lowerFilter, const std::vector<signedPixel>& upperFilter, size_t& realSize) {
    std::vector<signedPixel> result;
    result.reserve(lowerFilter.size());
    realSize = 0;
    
    for (size_t index = 0; index < lowerFilter.size(); index += 2) {
        result.push_back(lowerFilter[index]);
        result.push_back(upperFilter[index]);
        realSize += 2;
    }

    if (lowerFilter.size() % 2 != 0) {
        result.push_back(lowerFilter[lowerFilter.size() - 1]);
        result.push_back(lowerFilter[lowerFilter.size() - 1]);
        realSize++;
    }

    return result;
}

std::vector<pixel> retrieveMap(const std::vector<signedPixel>& lowerFilter, const std::vector<signedPixel>& upperFilter, size_t& realSize) {

    std::vector<pixel> result;
    result.reserve(lowerFilter.size());

    auto temp = lowerFilter[0] + upperFilter[0];
    result.push_back(pixel{(uint8_t)temp.red, (uint8_t)temp.green, (uint8_t)temp.blue});

    for (size_t index = 1; index < lowerFilter.size() - (realSize % 2 != 0); index++) {
        signedPixel temp = lowerFilter[index] + upperFilter[index];
        signedPixel temp2 = lowerFilter[index];
        temp2.red = 2 * temp2.red - temp.red;
        temp2.green = 2 * temp2.green - temp.green;
        temp2.blue = 2 * temp2.blue - temp.blue;
        result.push_back((pixel){(uint8_t)temp.red, (uint8_t)temp.green, (uint8_t)temp.blue});
        result.push_back((pixel){(uint8_t)temp2.red, (uint8_t)temp2.green, (uint8_t)temp2.blue});
    }
    if (realSize % 2 != 0) {
        auto temp = lowerFilter[lowerFilter.size() - 1] + upperFilter[upperFilter.size() - 1];
        result.push_back((pixel){(uint8_t)temp.red, (uint8_t)temp.green, (uint8_t)temp.blue});
    }

    return result;
}

void splitMap(std::vector<signedPixel>& lower, std::vector<signedPixel>& upper, const std::vector<pixel>& source) {
    lower.reserve(source.size());
    upper.reserve(source.size());

    for (size_t index = 0; index < source.size(); index++) {
        if (index % 2 == 0) {
            lower.push_back(source[index]);
        } else {
            upper.push_back(source[index]);
        }
    }
}