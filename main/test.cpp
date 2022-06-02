#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <iostream>
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
#include "tgaPersister.hpp"


int main (int argv, char** argc) {
    
    TgaAdapter adapter;
    TGAHeader header;
    adapter.openFile(argc[1]);
    adapter.getHeader(&header);
    std::vector<pixel> image = adapter.retrieve();

    TGAHeader headerCopy = header;

    BitFiles bitFiles;
    bitFiles.persistImage("tempImage", 8, image.size(), image, &header);

    uint8_t temp;
    uint64_t temp2;
    image = bitFiles.retrieveImage("tempImage", temp, temp2, &header);

    std::cout<<(int)header.img_t<<std::endl;
    //assert(memcmp(&header, &headerCopy, sizeof(TGAHeader)) == 0);

    TgaPersister persister;
    persister.persistImage(argc[2], temp2, image, &header);

    adapter.closeFile();

}