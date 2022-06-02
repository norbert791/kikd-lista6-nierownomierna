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
#include "functions.hpp"

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
    
    std::vector<pixel> image = tgaAdapter.retrieve();
    std::unique_ptr<Filter> filter = std::make_unique<LowerFilter>();

    std::vector<signedPixel> filteredImage = filter->applyFilter(image);

    filter = std::make_unique<UpperFilter>();
    std::vector<signedPixel> filteredImage2 = filter->applyFilter(image);

    size_t res = 0;
    auto temp = mergeMapping(filteredImage, filteredImage2, res);

    std::vector<signedPixel> t1, t2;
    t1.reserve(filteredImage.size() / 2);
    t2.reserve(filteredImage.size() / 2);

    for (size_t i = 0; i < temp.size(); i += 2) {
        if(i % 2 == 0) {
            t1.push_back(temp[i]);
        }
        else {
            t2.push_back(temp[i]);
        }
    }

    auto temp2 = retrieveMap(t1, t2, res);

    if (!tgaAdapter.persistCopy(temp2, "encoded.tga") ) {
        perror("Persisting failed");
        tgaAdapter.closeFile();
        return EXIT_FAILURE;
    }

    tgaAdapter.closeFile();

    return 0;
}