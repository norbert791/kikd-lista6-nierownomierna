#ifndef LOWER_FILTER_HPP
#define LOWER_FILTER_HPP

#include <vector>
#include "Filter.hpp"

class LowerFilter : public Filter {
    public:
        std::vector<signedPixel> applyFilter(const std::vector<pixel>& image) override;
        std::vector<signedPixel> removeFilter(const std::vector<signedPixel>& filteredImage) override;
        ~LowerFilter() = default;
    private:
        uint8_t meanValue (uint8_t num1, uint8_t num2) const;
};


#endif