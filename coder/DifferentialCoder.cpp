
#include "DifferentialCoder.hpp"


std::vector<signedPixel> DifferentialCoder::encode(const std::vector<signedPixel>& image) {
    std::vector<signedPixel> encodedImage;
    encodedImage.reserve(image.size());
    signedPixel previousPixel = image[0];
    encodedImage.push_back(image[0]);

    for (int i = 1; i < image.size(); i++) {
        signedPixel currentPixel = image[i];
        signedPixel difference;

        difference.red = currentPixel.red - previousPixel.red;
        difference.green = currentPixel.green - previousPixel.green;
        difference.blue = currentPixel.blue - previousPixel.blue;

        encodedImage.push_back(difference);
        previousPixel = currentPixel;
    }
    return encodedImage;
}

std::vector<signedPixel> DifferentialCoder::decode(const std::vector<signedPixel>& image) {
    std::vector<signedPixel> decodedImage;
    decodedImage.reserve(image.size());
    signedPixel previousPixel = image[0];
    decodedImage.push_back(image[0]);

    for (int i = 1; i < image.size(); i++) {
        signedPixel currentPixel = image[i];
        signedPixel decodedPixel;

        decodedPixel.red = previousPixel.red + currentPixel.red;
        decodedPixel.green = previousPixel.green + currentPixel.green;
        decodedPixel.blue = previousPixel.blue + currentPixel.blue;

        decodedImage.push_back(decodedPixel);
        previousPixel = decodedPixel;
    }
    return decodedImage;
}

