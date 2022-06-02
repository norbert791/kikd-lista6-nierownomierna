#include <iostream>
#include <algorithm>
#include "NonUniformConstQuantizer.hpp"


NonUniformConstQuantizer::NonUniformConstQuantizer(uint8_t bitsPerPixel) : bitsPerPixel(bitsPerPixel) {
    this->levels = bitsPerPixel;
}

std::vector<signedPixel> NonUniformConstQuantizer::encode(const std::vector<signedPixel>& image, uint8_t bitsPerPixel) {

    auto quants = generateQuants(bitsPerPixel);
    
    std::unordered_map<int16_t, int16_t> map;

    for (int i = 0; i < quants.size(); i++) {
        map[quants[i]] = i;
    }

    std::vector<signedPixel> result;
    result.reserve(image.size());

    auto fun = [&map, &quants](const signedPixel& pix){
        auto r = std::lower_bound(quants.begin(), quants.end(), pix.red);
        auto g = std::lower_bound(quants.begin(), quants.end(), pix.green);
        auto b = std::lower_bound(quants.begin(), quants.end(), pix.blue);

        return (signedPixel){map[*r], map[*g], map[*b]};
    };

    for (auto& pixel : image) {
        result.push_back(fun(pixel));
    }

    return result;
}

std::vector<signedPixel> NonUniformConstQuantizer::decode(const std::vector<signedPixel>& image) {
    
    auto quants = generateQuants(this->levels);
    std::unordered_map<int16_t, int16_t> map;

    for (int i = 0; i < quants.size(); i++) {
        map[i] = quants[i];
    }
    std::vector<signedPixel> result;
    result.reserve(image.size());

    for (auto it : image) {
        result.push_back(signedPixel{map[it.red], map[it.green], map[it.blue]});
    }
    return result;
}

std::vector<int16_t> NonUniformConstQuantizer::generateQuants(uint8_t bitsPerPixel) {
    
    switch(bitsPerPixel) {
        case 0:
            return {0};
        case 1:
            return {0,1};
        case 2:
            return {-1,0,1,2};
    }

    size_t numberOfColors = 1 << (bitsPerPixel - 1);
    std::vector<int16_t> quants;
    size_t pool = numberOfColors;
    size_t iteration = 2;

    while (iteration < 128) {
        size_t subPool = pool / iteration;
        size_t min = 0;
        size_t max = 8;
        pool -= subPool;

        if (max - min >= subPool) {
            for (size_t i = min; i < max; i++) {
                quants.push_back(i);
                subPool--;
            }
        }
        else {
            size_t step = (max - min) / subPool + ((max - min) % subPool != 0);
           for (size_t i = min; subPool > 0; i += step) {
                quants.push_back(i);
                subPool--;
            }
        }
        pool += subPool;

        min = max;
        max *= 2;
        iteration *= 2;
    }

    size_t step = (max - min) / pool + ((max - min) % pool != 0);

    while (pool > 0) {
        quants.push_back(min + step * pool);
        pool--;
    }

    for (size_t i = 1; i < quants.size(); i++) {
        quants.push_back(-quants[i]);
    }
    std::sort(quants.begin(), quants.end());
    
    return quants;
}
