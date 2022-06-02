#include <memory>
#include <iostream>
#include <cstring>
#include "TgaAdapter.hpp"
#include "Coder.hpp"
#include "DifferentialCoder.hpp"
#include "NonUniformQuantizer.hpp"
#include "Filter.hpp"
#include "LowerFilter.hpp"
#include "UpperFilter.hpp"
#include "NonUniformConstQuantizer.hpp"
#include "tgaPersister.hpp"
#include "bitFiles.hpp"
#include "functions.hpp"

int main (int argv, char** argc) {

    if (argv < 3) {
        std::cerr<<"Input name and output name requiered"<<std::endl;
        return EXIT_FAILURE;
    }
    std::vector<signedPixel> image;
    uint64_t uncompressedSize;
    uint8_t bitsPerPixel;
    BitFiles bitFiles;
    TGAHeader header;
    std::vector<pixel> retrieved = bitFiles.retrieveImage(argc[1], bitsPerPixel, uncompressedSize, &header);
       

    std::vector<signedPixel> filteredImage;
    std::vector<signedPixel> filteredImage2;

    std::unique_ptr<Quantizer> quantizer = std::make_unique<NonUniformConstQuantizer>(bitsPerPixel);
    
    splitMap(filteredImage, filteredImage2, retrieved);

    filteredImage2 = quantizer->decode(filteredImage2);
    filteredImage = quantizer->decode(filteredImage);

    auto result = retrieveMap(filteredImage, filteredImage2, uncompressedSize);

    TgaPersister tgaPersister;

    tgaPersister.persistImage(argc[2], uncompressedSize, result, &header);

    return 0;
}