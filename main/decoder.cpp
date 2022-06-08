#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
#include "TgaAdapter.hpp"
#include "Coder.hpp"
#include "DifferentialCoder.hpp"
#include "Filter.hpp"
#include "LowerFilterProcess.hpp"
#include "UpperFilterProcess.hpp"
#include "FilterQuantizer.hpp"
#include "UniformFilterQuantizer.hpp"
#include "tgaPersister.hpp"
#include "bitFiles.hpp"
#include "functions.hpp"

int main (int argc, char** argv) {

    if (argc < 3) {
        std::cerr<<"Input name and output name requiered"<<std::endl;
        return EXIT_FAILURE;
    }
    std::vector<signedPixel> image;
    uint64_t uncompressedSize;
    uint8_t bitsPerPixel;
    BitFiles bitFiles;
    TGAHeader header;
    std::vector<pixel> retrieved = bitFiles.retrieveImage(argv[1], bitsPerPixel, uncompressedSize, &header);
    

    std::vector<signedPixel> filteredImage;
    std::vector<signedPixel> filteredImage2;
    
    splitMap(filteredImage, filteredImage2, retrieved);

    std::unique_ptr<Filter> filter = std::make_unique<UpperFilterProcess>(std::make_unique<UniformFilterQuantizer>(bitsPerPixel));   

    //filteredImage2 = filter->removeFilter(filteredImage2);

    //filter = std::make_unique<LowerFilterProcess>(std::make_unique<UniformFilterQuantizer>(bitsPerPixel));

    filteredImage = filter->removeFilter(filteredImage);


    size_t tempSize = uncompressedSize;
    auto result = retrieveMap(filteredImage, filteredImage2, tempSize);
    //assert(uncompressedSize == header.width * header.height);
    TgaPersister tgaPersister;

    tgaPersister.persistImage(argv[2], uncompressedSize, result, &header);

    return 0;
}