#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
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

int main (int argv, char** argc) {
    
    if (argv < 4) {
        std::cerr<<"Input name output name and k requiered"<<std::endl;
        return EXIT_FAILURE;
    }
    uint8_t k = atoi(argc[3]);
    if (k == 0 || k > 7) {
        std::cerr<<"k must be in range 1-7"<<std::endl;
        return EXIT_FAILURE;
    }

    TgaAdapter tgaAdapter;

    if (!tgaAdapter.openFile(argc[1])) {
        std::cerr<<"Opening failed"<<std::endl;
        return EXIT_FAILURE;
    }
    
    std::unique_ptr<Quantizer> quantizer = std::make_unique<NonUniformConstQuantizer>(k);
    std::vector<pixel> image = tgaAdapter.retrieve();
    
    std::unique_ptr<Filter> filter = std::make_unique<LowerFilter>();

    std::vector<signedPixel> filteredImage = filter->applyFilter(image);

    filter = std::make_unique<UpperFilter>();
    std::vector<signedPixel> filteredImage2 = filter->applyFilter(image);

    size_t res = 0;

    filteredImage = quantizer->encode(filteredImage, k);
    filteredImage2 = quantizer->encode(filteredImage2, k);

    auto temp = mergeMapping(filteredImage, filteredImage2, res);

    BitFiles bitFiles;


    std::vector<pixel> result;

    for (auto pix : temp) {
        result.push_back(pixel{(uint8_t)pix.red, (uint8_t)pix.green, (uint8_t)pix.blue});
    }

    TGAHeader header;
    tgaAdapter.getHeader(&header);
    
    bitFiles.persistImage(argc[2], k, res, result, &header);
    tgaAdapter.closeFile();

    return 0;
}