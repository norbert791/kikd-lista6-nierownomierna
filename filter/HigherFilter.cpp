#include <iostream>
#include "HigherFilter.hpp"


std::vector<signedPixel> HigherFilter::applyFilter(const std::vector<pixel>& image) {

    std::vector<signedPixel> result(image.size(), {0,0,0});

    result[0] = image[0];

    for (size_t i = 1; i < image.size(); i++) {
        result[i].red = (image[i].red - image[i - 1].red) / 2;
        result[i].green = (image[i].green - image[i - 1].green) / 2;
        result[i].blue = (image[i].blue - image[i - 1].blue) / 2;
    }

    return result;
}

std::vector<pixel> HigherFilter::removeFilter(const std::vector<signedPixel>& filteredImage) {
    
    std::vector<pixel> result(filteredImage.size(), {0,0,0});

    result[0].red = filteredImage[0].red;
    result[0].green = filteredImage[0].green;
    result[0].blue = filteredImage[0].blue;


    for(size_t i = 1; i < filteredImage.size(); i++) {
        result[i].red = 2 * filteredImage[i].red + filteredImage[i - 1].red;
        result[i].green = 2 * filteredImage[i].green + filteredImage[i - 1].green;
        result[i].blue = 2 * filteredImage[i].blue + filteredImage[i - 1].blue;
    }

    return result;
}