#ifndef TGA_ADAPTER_H
#define TGA_ADAPTER_H

#include <vector>
#include <tga.h>
#include "image.h"

class TgaAdapter {

    public:
        bool openFile(const char* name);
        std::vector<pixel> retrieve();

        bool persistCopy(std::vector<pixel>, const char* name);
        void closeFile();
    private:
        TGA* tga;
        TGAData data;
        size_t width = 0;
        size_t height = 0;
        std::vector<pixel> image;
};

#endif