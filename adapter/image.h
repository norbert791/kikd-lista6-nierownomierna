#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <iostream>
#include <cmath>

typedef struct signedPixel signedPixel;

typedef struct pixel{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    pixel(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {};
    pixel() = default;
} pixel; 

bool operator<(const pixel& left, const pixel& right);

typedef struct signedPixel{

    int16_t red;
    int16_t green;
    int16_t blue;

    signedPixel() = default;
    signedPixel(pixel pix) {
        red = pix.red;
        green = pix.green;
        blue = pix.blue;
    }
    signedPixel(int16_t red, int16_t green, int16_t blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
   /* signedPixel(float red, float green, float blue) {
        this->red = (int16_t) float(red);
        this->green = (int16_t) float(green);
        this->blue = (int16_t) float(blue);
    }*/
} signedPixel;

bool operator<(const signedPixel& left, const signedPixel& right);

signedPixel operator+(const signedPixel& left, const signedPixel& right);
signedPixel operator-(const signedPixel& left, const signedPixel& right);
/*
class myComp {
    public:
        bool operator()(pixel left, pixel right) const {
            uint32_t temp1 = ((uint32_t)left.red <<16) + ((uint32_t)left.green <<8) + ((uint32_t)left.blue);
            uint32_t temp2 = ((uint32_t)right.red <<16) + ((uint32_t)right.green <<8) + ((uint32_t)right.blue);
            return temp1 > temp2;
        }

};*/


typedef struct floatPixel{

    float red;
    float green;
    float blue;

    floatPixel() = default;
    floatPixel(pixel pix) {
        red = pix.red * 1.0f;
        green = pix.green * 1.0f;
        blue = pix.blue * 1.0f;
    }
    floatPixel(float red, float green, float blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
} floatPixel;

bool operator<(const floatPixel& left, const floatPixel& right);

floatPixel operator+(const floatPixel& left, const floatPixel& right);
floatPixel operator-(const floatPixel& left, const floatPixel& right);

#endif