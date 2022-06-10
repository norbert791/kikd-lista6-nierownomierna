#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <iostream>
#include <functional>
#include "TgaAdapter.hpp"
#include "Coder.hpp"
#include "DifferentialCoder.hpp"
#include "NonUniformQuantizer.hpp"
#include "Filter.hpp"
#include "LowerFilter.hpp"
#include "UpperFilter.hpp"
#include "NonUniformConstQuantizer.hpp"
#include "functions.hpp"
#include "bitFiles.hpp"
#include "tgaPersister.hpp"
#include "LowerFilterProcess.hpp"
#include "UpperFilterProcess.hpp"
#include "FilterQuantizer.hpp"
#include "UniformFilterQuantizer.hpp"
#include "IdQuantizer.hpp"

 

int main (int argv, char** argc) {
    
    TgaAdapter adapter;
    TGAHeader header;
    adapter.openFile(argc[1]);
    adapter.getHeader(&header);
    std::vector<pixel> image = adapter.retrieve();
    
    for (auto pix : image) {
        //std::cout<<(int) pix.red<<" "<<(int) pix.green<<" "<<(int) pix.blue<<std::endl;
    }
    std::cout<<"-----------------------------------------------------"<<std::endl;
    
    std::unique_ptr<Filter> filter = std::make_unique<LowerFilterProcess>(std::make_unique<IdQuantizer>());
    std::vector<signedPixel> filteredImage = filter->applyFilter(image);
    auto unfilteredImage = filter->removeFilter(filteredImage);    
    filter = std::make_unique<UpperFilterProcess>(std::make_unique<IdQuantizer>()); 
    std::vector<signedPixel> filteredImage2 = filter->applyFilter(image);
    auto unfilteredImage2 = filter->removeFilter(filteredImage2);

    std::vector<pixel> result;
    result.reserve(filteredImage.size());

    for (size_t i = 1; i < filteredImage.size(); i++) {
       // std::cout<<filteredImage[i].red<<" "<<filteredImage[i].green<<" "<<filteredImage[i].blue<<std::endl;
       // std::cout<<filteredImage[i].red - unfilteredImage[i].red<<" "<<filteredImage[i].green - unfilteredImage[i].green<<" "<<filteredImage[i].blue - unfilteredImage[i].green<<std::endl;
        //auto temp0 = signedPixel(image[i]) + signedPixel(image[i - 1]) - signedPixel(unfilteredImage[i].red * 2, unfilteredImage[i].green * 2, unfilteredImage[i].blue * 2);
        //std::cout<<temp0.red<<" "<<temp0.green<<" "<<temp0.blue<<std::endl;

        auto temp = signedPixel(image[i]) - signedPixel(image[i - 1]) - signedPixel(unfilteredImage2[i].red * 2, unfilteredImage2[i].green * 2, unfilteredImage2[i].blue * 2);
        std::cout<<temp.red<<" "<<temp.green<<" "<<temp.blue<<std::endl;
    }

    for (size_t i = 0; i < filteredImage.size(); i++) {
        result.push_back(pixel{(uint8_t)(unfilteredImage[i].red + unfilteredImage2[i].red), (uint8_t)(unfilteredImage[i].green + unfilteredImage2[i].green), (uint8_t)(unfilteredImage[i].blue + unfilteredImage2[i].blue)});
    }

    TgaPersister persister;
    adapter.persistCopy(result, argc[2]);
}