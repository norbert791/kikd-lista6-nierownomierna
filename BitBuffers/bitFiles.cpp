#include "bitFiles.hpp"

#include <cstring>

void persistImage(const char* fileName, uint8_t bitsPerPixel,
                    uint64_t uncompressedSize, const std::vector<pixel>& pixels) {

    BitWriter writer;

    auto writeByte = [&writer](uint8_t byte){
        for (size_t i = 0; i < 8; i++) {
            writer.writeBit(byte & 0x80 == 0x80); //bx10000000
            byte << 1;
        }
    };

    writer.open(fileName);

    writeByte(bitsPerPixel);
    char tempBytes[8];
    std::memcpy(tempBytes, &uncompressedSize, sizeof(uncompressedSize));
    
    for (size_t i = 0; i < 8; i++) {
        writeByte(tempBytes[i]);
    }
    for (auto pix : pixels) {
        writeByte(pix.red);
        writeByte(pix.green);
        writeByte(pix.blue);
    }
    writer.close();
}

std::vector<pixel> retrieveImage(const char* filename) {

    BitReader reader;
    reader.open(filename);

    auto readByte = [&reader]() -> uint8_t{
        uint8_t result = 0;

        for (size_t i = 0; i < 8; i++) {
            result = (result << 1) + reader.getBit() == true ? 1 : 0;
        }

        return result;
    };

    
}