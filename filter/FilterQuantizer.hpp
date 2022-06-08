#ifndef FILTER_QUANTIZER_HPP
#define FILTER_QUANTIZER_HPP

#include <iostream>
#include "image.h"


class FilterQuantizer {

    public:
       virtual signedPixel assignQuant(signedPixel pixel) = 0;
       virtual std::vector<signedPixel> mapToIndexes(const std::vector<signedPixel>& image) = 0;
       virtual signedPixel getQuantVector(signedPixel index) = 0;
       virtual ~FilterQuantizer() = default;
};



#endif