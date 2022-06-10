#include "LowerFilterProcess.hpp"
#include <iostream>
#include <set>

std::vector<signedPixel> LowerFilterProcess::applyFilter(const std::vector<pixel>& image) {

    std::set<signedPixel> vals;
    std::set<signedPixel> inds;

    std::vector<signedPixel> result(image.size(), {0,0,0});

    //std::cout<<(int)image[0].red<<" "<<(int)image[0].green<<" "<<(int)image[0].blue<<std::endl;
    result[0] = image[0];
    //std::cout<<"result[0] = "<<result[0].red<<" "<<result[0].green<<" "<<result[0].blue<<std::endl;
    for (size_t i = 1; i < image.size(); i++) {
        signedPixel filteredPixel = {(int16_t) ((int16_t) image[i].red / 2 + (int16_t) image[i - 1].red / 2 + (image[i].red & image[i - 1].red & 1)),
                            (int16_t) ((int16_t) image[i].green / 2 + (int16_t) image[i - 1].green / 2 + (image[i].green & image[i - 1].green & 1)), 
                            (int16_t) ((int16_t) image[i].blue / 2 + (int16_t) image[i - 1].blue / 2 + (image[i].blue & image[i - 1].blue & 1))};
        //std::cout<<filteredPixel.red<<" "<<filteredPixel.green<<" "<<filteredPixel.blue<<std::endl;
        result[i] = filteredPixel;
    }

    std::vector<signedPixel> finalResult;
    finalResult.reserve(result.size());

    finalResult[0] = quantizer->assignQuant(result[0]);
    signedPixel lastError = finalResult[0] - result[0];
    for (size_t i = 1; i < result.size(); i++) {
        signedPixel temp = result[i] - result[i - 1] + lastError;
        finalResult[i] = quantizer->assignQuant(temp);
       // std::cout<<finalResult[i].red<<" "<<finalResult[i].green<<" "<<finalResult[i].blue<<std::endl;
        lastError = result[i] - finalResult[i];
        inds.insert(finalResult[i]);
    }
   .. std::cout<<"inds.size() = "<<inds.size()<<std::endl;
    return quantizer->mapToIndexes(result);
}

std::vector<signedPixel> LowerFilterProcess::removeFilter(const std::vector<signedPixel>& filteredImage) {
    std::vector<signedPixel> result;
    result.reserve(filteredImage.size());

    for (auto pix : filteredImage) {
        result.push_back(quantizer->getQuantVector(pix));
    }
    
    std::vector<signedPixel> finalResult;
    finalResult.reserve(result.size());

    finalResult.push_back(result[0]);

   // std::cout<<result[0].red<<" "<<result[0].green<<" "<<result[0].blue<<std::endl;
    for (size_t i = 1; i < result.size(); i++) {
        finalResult.push_back(finalResult[i - 1] + result[i]);
        //std::cout<<result[i].red<<" "<<result[i].green<<" "<<result[i].blue<<std::endl;
        //std::cout<<finalResult[i].red<<" "<<finalResult[i].green<<" "<<finalResult[i].blue<<std::endl;
    }

    return finalResult;
}
LowerFilterProcess::LowerFilterProcess(std::unique_ptr<FilterQuantizer> quantizer) : quantizer(std::move(quantizer)) {}



