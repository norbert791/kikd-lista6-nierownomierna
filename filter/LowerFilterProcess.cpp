#include "LowerFilterProcess.hpp"

std::vector<signedPixel> LowerFilterProcess::applyFilter(const std::vector<pixel>& image) {

    std::vector<signedPixel> result(image.size(), {0,0,0});

    result[0] = quantizer->assignQuant(image[0]);

    for (size_t i = 1; i < image.size(); i++) {
        signedPixel temp = {image[i].red - result[i - 1].red, image[i].green - result[i - 1].green, image[i].blue - result[i - 1].blue};
        result[i] = temp;
    }

    return quantizer->mapToIndexes(result);
}

std::vector<signedPixel> LowerFilterProcess::removeFilter(const std::vector<signedPixel>& filteredImage) {
        std::vector<signedPixel> result;
    result.reserve(filteredImage.size());

    for (auto pix : filteredImage) {
        result.push_back(quantizer->getQuantVector(pix));
    }
    
    return result;
}
LowerFilterProcess::LowerFilterProcess(std::unique_ptr<FilterQuantizer> quantizer) : quantizer(std::move(quantizer)) {}



