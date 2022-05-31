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

int main (int argv, char** argc) {
    
    if (argv < 3) {
        std::cerr<<"Input name and k requiered"<<std::endl;
        return EXIT_FAILURE;
    }
    uint8_t k = atoi(argc[2]);
    if (k == 0 || k > 7) {
        std::cerr<<"k must be in range 1-7"<<std::endl;
        return EXIT_FAILURE;
    }

    TgaAdapter tgaAdapter;

    if (!tgaAdapter.openFile(argc[1])) {
        std::cerr<<"Opening failed"<<std::endl;
        return EXIT_FAILURE;
    }
    
    std::unique_ptr<Filter> filter = std::make_unique<LowerFilter>();

    std::unique_ptr<Coder> coder = std::make_unique<DifferentialCoder>();

    std::vector<pixel> image = tgaAdapter.retrieve();

    std::vector<signedPixel> filteredImage = filter->applyFilter(image);
    std::vector<signedPixel> encodedImage = coder->encode(filteredImage);

    if (!tgaAdapter.persistCopy(encodedImage, "encoded_low.tga") ) {
        perror("Persisting failed");
        tgaAdapter.closeFile();
        return EXIT_FAILURE;
    }

    filter = std::make_unique<UpperFilter>();
    std::unique_ptr<Quantizer> quantizer = std::make_unique<NonUniformQuantizer>();

    filteredImage = filter->applyFilter(image);
    encodedImage = quantizer->encode(filteredImage, k);

    if (!tgaAdapter.persistCopy(encodedImage, "encoded_high.tga") ) {
        perror("Persisting failed");
        tgaAdapter.closeFile();
        return EXIT_FAILURE;
    }

    tgaAdapter.closeFile();

    return 0;
}