#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
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


double mean_squere_error(size_t height, size_t width, std::vector<pixel> encoded,
                        std::vector<pixel> original, std::function<uint32_t(pixel)> cast) {
    double result = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            double temp = 1.0 * cast(encoded[i * width + j]) - cast(original[i * width + j]);
            result += temp * temp;
        }
    }
    return result / (width * height);
}

double signal_to_noise_ratio(size_t height, size_t width, std::vector<pixel> original,
                            std::function<uint32_t(pixel)> cast, double mse) {

    double result = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            double temp = cast(original[i * width + j]);
            result += temp * temp;
        }
    }
    result /= height * width;
    return result / mse;
}

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr<<"Two filenames requiered"<<std::endl;
        return EXIT_FAILURE;
    }

    std::vector<signedPixel> image;
    uint64_t uncompressedSize;
    uint8_t bitsPerPixel;
    BitFiles bitFiles;
    TGAHeader header;
    std::vector<pixel> retrieved = bitFiles.retrieveImage(argv[2], bitsPerPixel, uncompressedSize, &header);
    

    std::vector<signedPixel> filteredImage;
    std::vector<signedPixel> filteredImage2;

    std::unique_ptr<Quantizer> quantizer = std::make_unique<NonUniformConstQuantizer>(bitsPerPixel);
    
    splitMap(filteredImage, filteredImage2, retrieved);

    filteredImage2 = quantizer->decode(filteredImage2);
    filteredImage = quantizer->decode(filteredImage);

    size_t tempSize = uncompressedSize;
    auto result = retrieveMap(filteredImage, filteredImage2, tempSize);

    TgaAdapter adapter;
    adapter.openFile(argv[1]);

    auto inputVector = adapter.retrieve();

    double mse[4] = {mean_squere_error(header.height, header.width, 
    inputVector, result, [](pixel pix){
        return ((uint32_t)pix.red) << 16 + ((uint32_t)pix.green) << 8 + pix.blue; }),
        mean_squere_error(header.height, header.width, inputVector, result, [](pixel pix){return pix.red;}),
        mean_squere_error(header.height, header.width, inputVector, result, [](pixel pix){return pix.green;}),
        mean_squere_error(header.height, header.width, inputVector, result, [](pixel pix){return pix.blue;})
    };
    
    double noise[4] = {signal_to_noise_ratio(header.height, header.width, 
    inputVector, [](pixel pix){
        return ((uint32_t)pix.red) << 16 + ((uint32_t)pix.green) << 8 + pix.blue; }, mse[0]),
        signal_to_noise_ratio(header.height, header.width, inputVector, [](pixel pix){return pix.red;}, mse[1]),
        signal_to_noise_ratio(header.height, header.width, inputVector, [](pixel pix){return pix.green;}, mse[1]),
        signal_to_noise_ratio(header.height, header.width, inputVector, [](pixel pix){return pix.blue;}, mse[1])
    };

    std::cout<<"Mse:\n";
    std::cout<<"total: "<<mse[0]<<"\n";
    std::cout<<"red: "<<mse[1]<<"\n";
    std::cout<<"green: "<<mse[2]<<"\n";
    std::cout<<"blue: "<<mse[3]<<"\n";

    std::cout<<"Noise:\n";
    std::cout<<"total: "<<noise[0]<<"\n";
    std::cout<<"red: "<<noise[1]<<"\n";
    std::cout<<"green: "<<noise[2]<<"\n";
    std::cout<<"blue: "<<noise[3]<<std::endl;

}