#include <unordered_map>
#include <numeric>
#include "NonUniformQuantizer.hpp"


std::vector<signedPixel> NonUniformQuantizer::encode(const std::vector<signedPixel>& image, uint8_t bitsPerColor) {

    auto v1 = quantize(image, [](signedPixel p) { return p.red; }, bitsPerColor);
    auto v2 = quantize(image, [](signedPixel p) { return p.green; }, bitsPerColor);
    auto v3 = quantize(image, [](signedPixel p) { return p.blue; }, bitsPerColor);

    std::vector<signedPixel> encodedImage;
    encodedImage.reserve(image.size());

    for (int i = 0; i < image.size(); i++) {
        signedPixel p = image[i];
        signedPixel encodedPixel;

        encodedPixel.red = v1[i];
        encodedPixel.green = v2[i];
        encodedPixel.blue = v3[i];

        encodedImage.push_back(encodedPixel);
    }

    return encodedImage;
}


std::vector<int16_t> NonUniformQuantizer::quantize(const std::vector<signedPixel>& image, std::function<int16_t(signedPixel)> cast, uint8_t bits) {
    if (bits > 8) {
        return std::vector<int16_t>();
    }
    
    std::unordered_map<int16_t, size_t> histogram;
    for (auto pixel : image) {
        int16_t quantizedPixel = cast(pixel);
        histogram[quantizedPixel]++;
    }

    uint8_t numOfValues = 255 >> (8 - bits) + 1;

    std::vector<int16_t> quantizedImage;

    for (auto it : histogram) {
        quantizedImage.push_back(it.first);
    }

    std::sort(quantizedImage.begin(), quantizedImage.end());

    std::unordered_map<int16_t, int16_t> newValues;

    uint16_t expectedProbability = image.size() / numOfValues;

    std::function<int16_t(std::vector<int16_t>::iterator, std::vector<int16_t>::iterator)> findQuant = [&](std::vector<int16_t>::iterator start, std::vector<int16_t>::iterator end) {
        
        int64_t result = 0;
        size_t tempSum = 0;

        for (auto it = start; it != end; it++) {
            tempSum += histogram[*it];
            result += *it * histogram[*it];
        }

        return result / tempSum;
    };

    std::vector<int16_t>::iterator start = quantizedImage.begin();

    std::vector<int16_t>::iterator end = quantizedImage.begin();

    size_t temp = 0;

    while (end != quantizedImage.end()) {
        temp += *end;
        if (temp >= expectedProbability) {
            auto result = findQuant(start, ++end);

            for (auto it = start; it != end; it++) {
                newValues[*it] = result;
            }
            start = end;
            continue;
        }
        end++;
    }

    std::vector<int16_t> result;
    result.reserve(image.size());

    for (auto it : image) {
        result.push_back(newValues[cast(it)]);
    }

    return result;
}

//compute distribution and randomly add new values
std::vector<signedPixel> NonUniformQuantizer::decode(const std::vector<signedPixel>& encoded) {
    std::vector<signedPixel> decoded;
    decoded.reserve(encoded.size());

    for (auto it : encoded) {
        signedPixel p;
        p.red = it.red;
        p.green = it.green;
        p.blue = it.blue;
        decoded.push_back(p);
    }

    return decoded;
}