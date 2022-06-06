#include <memory>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <iostream>
#include <functional>
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
    auto headerCopy = header;

/*
    BitWriter chuj = BitWriter();
    chuj.open("chujTest.txt");
    uint8_t buff[sizeof(TGAHeader)];
    memcpy(buff, &header, sizeof(TGAHeader));
    for (size_t i = 0; i < sizeof(TGAHeader); i++) {
        for (size_t j = 0; j < 8; j++) {
            chuj.writeBit((buff[i] & 0x80) == 0x80);
            buff[i] <<= 1;
        }
    }
    chuj.close();

    BitReader chuj2 = BitReader();
    chuj2.open("chujTest.txt");
    uint8_t buff2[sizeof(TGAHeader)];
    for (size_t i = 0; i < sizeof(TGAHeader); i++) {
        for (size_t j = 0; j < 8; j++) {
            buff2[i] <<= 1;
            buff2[i] |= chuj2.getBit() ? 1 : 0;
        }
    }
    memcpy(&header, buff2, sizeof(TGAHeader));

    std::cout<<header.width<<std::endl;*/

    BitFiles bitFiles;
    bitFiles.persistImage("tempImage", 8, image.size(), image, &header);

    uint8_t temp;
    uint64_t temp2;
    image = bitFiles.retrieveImage("tempImage", temp, temp2, &header);

    assert(temp2 == header.width * header.height);
   // std::cout<<(int)header.img_t<<std::endl;
    //std::cout<<(int)header.width<<std::endl;
    std::cout<<(int)temp<<std::endl;
    std::cout<<(int)temp2<<std::endl;
    //assert(memcmp(&header, &headerCopy, sizeof(TGAHeader)) == 0);

    TgaPersister persister;
    persister.persistImage(argc[2], temp2, image, &header);

    adapter.closeFile();


}