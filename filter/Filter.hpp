#ifndef FILTER_HPP
#define FILTER_HPP

#include <vector>
#include "image.h"

class Filter {
    public:
        virtual std::vector<signedPixel> applyFilter(const std::vector<pixel>& image) = 0;
        virtual std::vector<pixel> removeFilter(const std::vector<signedPixel>& filteredImage) = 0;
        virtual ~Filter() = default;
};



#endif