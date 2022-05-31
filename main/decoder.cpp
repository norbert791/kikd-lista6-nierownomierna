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

    if (argv < 4) {
        std::cerr<<"Input name, output name and k requiered"<<std::endl;
        return EXIT_FAILURE;
    }
    TgaAdapter tgaAdapter;
    switch (argc[3][0]) {
        case 'l':
            if (tgaAdapter.openFile(argc[1])) {

                std::unique_ptr<Filter> filter = std::make_unique<LowerFilter>();

                std::unique_ptr<Coder> coder = std::make_unique<DifferentialCoder>();

                std::vector<pixel> image = tgaAdapter.retrieve();

                std::vector<signedPixel> temp;
                temp.reserve(image.size());
                for (auto pix : image) {
                    temp.push_back({pix.red, pix.green, pix.blue});
                }

                std::vector<signedPixel> decodedImage = coder->decode(temp);
                
                std::vector<pixel> unfilteredImage = filter->removeFilter(decodedImage);

                if (!tgaAdapter.persistCopy(unfilteredImage, argc[2]) ) {
                    perror("Persisting failed");
                    tgaAdapter.closeFile();
                    return EXIT_FAILURE;
                }

                tgaAdapter.closeFile();
            }
            else {
                std::cerr<<"Opening failed"<<std::endl;
                return EXIT_FAILURE;
            }
            break;

        case 'h':
            if (tgaAdapter.openFile(argc[1])) {

                std::unique_ptr<Filter> filter = std::make_unique<UpperFilter>();

                std::unique_ptr<Quantizer> quantizer = std::make_unique<NonUniformQuantizer>();

                std::vector<pixel> image = tgaAdapter.retrieve();

                std::vector<signedPixel> temp;
                temp.reserve(image.size());
                for (auto pix : image) {
                    temp.push_back({pix.red, pix.green, pix.blue});
                }

                std::vector<signedPixel> decodedImage = quantizer->decode(temp);
                std::vector<pixel> unfilteredImage = filter->removeFilter(decodedImage);

                if (!tgaAdapter.persistCopy(unfilteredImage, argc[2]) ) {
                    perror("Persisting failed");
                    tgaAdapter.closeFile();
                    return EXIT_FAILURE;
                }

                tgaAdapter.closeFile();
            }
            else {
                std::cerr<<"Opening failed"<<std::endl;
                return EXIT_FAILURE;
            }
            break;
        default:
            std::cerr<<"l=low h=hight"<<std::endl;
            return EXIT_FAILURE;
    }
    return 0;
}