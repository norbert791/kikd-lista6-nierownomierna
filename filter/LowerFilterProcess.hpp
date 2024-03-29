#ifndef LOWER_FILTER_PROCESS_HPP
#define LOWER_FILTER_PROCESS_HPP

#include <vector>
#include <memory>
#include "Filter.hpp"
#include "FilterQuantizer.hpp"


class LowerFilterProcess: public Filter {
    public:
        std::vector<signedPixel> applyFilter(const std::vector<pixel>& image) override;
        std::vector<signedPixel> removeFilter(const std::vector<signedPixel>& filteredImage) override;
        LowerFilterProcess(std::unique_ptr<FilterQuantizer> quantizer);
        ~LowerFilterProcess() = default;
    private:
        inline uint8_t meanValue (uint8_t num1, uint8_t num2) const;
        std::unique_ptr<FilterQuantizer> quantizer;

};

#endif //LOWER_FILTER_QUANTIZER_HPP