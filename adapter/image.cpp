#include "image.h"



bool operator<(const pixel& left, const pixel& right) {
    uint32_t temp1 = ((uint32_t)left.red <<16) + ((uint32_t)left.green <<8) + ((uint32_t)left.blue);
    uint32_t temp2 = ((uint32_t)right.red <<16) + ((uint32_t)right.green <<8) + ((uint32_t)right.blue);
    return temp1 < temp2;
}

bool operator<(const signedPixel& left, const signedPixel& right) {
    uint32_t temp1 = ((uint32_t)left.red <<16) + ((uint32_t)left.green <<8) + ((uint32_t)left.blue);
    uint32_t temp2 = ((uint32_t)right.red <<16) + ((uint32_t)right.green <<8) + ((uint32_t)right.blue);

    return temp1 < temp2;
}
signedPixel operator+(const signedPixel& left, const signedPixel& right) {
    return signedPixel{(int16_t)(left.red + right.red), (int16_t)(left.green + right.green), (int16_t)(left.blue + right.blue)};
}
signedPixel operator-(const signedPixel& left, const signedPixel& right) {
    return signedPixel{(int16_t)(left.red - right.red), (int16_t)(left.green - right.green), (int16_t)(left.blue - right.blue)};
}


bool operator<(const floatPixel& left, const floatPixel& right) {
    auto temp = left.red * 65536.0f * 1.0f + left.green * 256.0f + left.blue;
    auto temp2 = right.red * 65536.0f * 1.0f + right.green * 256.0f + right.blue;
    return temp < temp2; 
}

floatPixel operator+(const floatPixel& left, const floatPixel& right) {
    return floatPixel{left.red + right.red, left.green + right.green, left.blue + right.blue};
}

floatPixel operator-(const floatPixel& left, const floatPixel& right) {
    return floatPixel{left.red - right.red, left.green - right.green, left.blue - right.blue};
}