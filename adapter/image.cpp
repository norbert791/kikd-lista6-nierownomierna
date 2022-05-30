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