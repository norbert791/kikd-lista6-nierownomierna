#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include "image.h"

std::vector<signedPixel> mergeMapping(const std::vector<signedPixel>& lowerFilter, const std::vector<signedPixel>& upperFilter, size_t& realSize);

std::vector<pixel> retrieveMap(const std::vector<signedPixel>& lowerFilter, const std::vector<signedPixel>& upperFilter, size_t& realSize);

void splitMap(std::vector<signedPixel>& lower, std::vector<signedPixel>& upper, const std::vector<pixel>& source);

#endif