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