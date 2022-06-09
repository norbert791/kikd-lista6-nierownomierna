#include "LowerFilterProcess.hpp"

std::vector<signedPixel> LowerFilterProcess::applyFilter(const std::vector<pixel>& image) {

    std::vector<signedPixel> result(image.size(), {0,0,0});

    //std::cout<<(int)image[0].red<<" "<<(int)image[0].green<<" "<<(int)image[0].blue<<std::endl;
    result[0] = quantizer->assignQuant(image[0]);
    //std::cout<<"result[0] = "<<result[0].red<<" "<<result[0].green<<" "<<result[0].blue<<std::endl;

    for (size_t i = 1; i < image.size(); i++) {
        signedPixel temp = {(int16_t) ((int16_t) image[i].red / 2 + image[i - 1].red / 2 + (image[i].red & image[i - 1].red & 1)),
                            (int16_t) ((int16_t) image[i].green / 2 + image[i - 1].green / 2 + (image[i].green & image[i - 1].green & 1)), 
                            (int16_t) ((int16_t) image[i].blue / 2 + image[i - 1].blue / 2 + (image[i].blue & image[i - 1].blue & 1))};
        //std::cout<<temp.red<<" "<<temp.green<<" "<<temp.blue<<std::endl;
        temp = temp - result[i - 1];  
        std::cout<<temp.red<<" "<<temp.green<<" "<<temp.blue<<std::endl;
        temp = quantizer->assignQuant(temp);      
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



