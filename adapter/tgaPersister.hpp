#ifndef TGA_PERSISTER_HPP
#define TGA_PERSISTER_HPP

#include <vector>
#include "image.h"

class TgaPersister {
    public:
        bool persistImage(const char* fileName, size_t size, const std::vector<pixel>& image, TGAHeader* header);
};



#endif