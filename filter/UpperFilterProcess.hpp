#ifndef UPPER_FILTER_PROCESS_HPP
#define UPPER_FILTER_PROCESS_HPP

#include <vector>
#include <memory>
#include "Filter.hpp"
#include "FilterQuantizer.hpp"


class UpperFilterProcess: public Filter {
    public:
        std::vector<signedPixel> applyFilter(const std::vector<pixel>& image) override;
        std::vector<signedPixel> removeFilter(const std::vector<signedPixel>& filteredImage) override;
        UpperFilterProcess(std::unique_ptr<FilterQuantizer> quantizer);
    private:
        inline uint8_t meanValue (uint8_t num1, uint8_t num2) const;
        std::unique_ptr<FilterQuantizer> quantizer;

};

#endif