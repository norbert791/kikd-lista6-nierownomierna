#include <tga.h>
#include "tgaPersister.hpp"
#include "cstring"

bool TgaPersister::persistImage(const char* fileName, size_t size, const std::vector<pixel>& image, TGAHeader *header) {
    
    TGA* output = TGAOpen(fileName, "w");
    if (!output || output->last != TGA_OK) {
        perror("opening error\n");
        return false;
    }

    memcpy(&(output->hdr), header, sizeof(*header));

    TGAData data;

    data.img_data = new uint8_t[size * 3];

    for (size_t i = 0; i < size; i++) {
        data.img_data[i * 3] = image[i].red;
        data.img_data[i * 3 + 1] = image[i].green;
        data.img_data[i * 3 + 2] = image[i].blue;
    }

    TGAWriteImage(output, &data);
    TGAClose(output);
    delete data.img_data;
    return true;
}