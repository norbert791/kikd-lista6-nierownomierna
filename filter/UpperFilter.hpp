#ifndef UPPER_FILTER_HPP
#define UPPER_FILTER_HPP

#include "Filter.hpp"

class UpperFilter : public Filter {
    public:
        virtual std::vector<signedPixel> applyFilter(const std::vector<pixel>& image) override;
        virtual std::vector<signedPixel> removeFilter(const std::vector<signedPixel>& filteredImage) override;
};



#endif