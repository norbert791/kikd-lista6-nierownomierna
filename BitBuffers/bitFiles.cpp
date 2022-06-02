#include "bitFiles.hpp"

#include <cstring>

void BitFiles::persistImage(const char* fileName, uint8_t bitsPerPixel,
                    uint64_t uncompressedSize, const std::vector<pixel>& pixels,
                    TGAHeader* header) {

    BitWriter writer;

    
    auto writeByte = [&writer](uint8_t byte, uint8_t bitsPerByte) {
        for (uint8_t i = 0; i < 8 - bitsPerByte; i++) {
            byte = byte << 1;
        }
        for (size_t i = 0; i < bitsPerByte; i++) {
            writer.writeBit(byte & 0x80 == 0x80); //bx10000000
            byte << 1;
        }
    };

    uint8_t headerCopy[sizeof(*header)];
    memcpy(headerCopy, header, sizeof(*header));

    writer.open(fileName);

    for (size_t i = 0; i < sizeof(*header); i++) {
        writeByte(headerCopy[i], 8);
    }

    writeByte(bitsPerPixel, 8);
    uint8_t tempBytes[8];
    std::memcpy(tempBytes, &uncompressedSize, sizeof(uncompressedSize));
    
    for (size_t i = 0; i < 8; i++) {
        writeByte(tempBytes[i], 8);
    }
    for (auto pix : pixels) {
        writeByte(pix.red, bitsPerPixel);
        writeByte(pix.green, bitsPerPixel);
        writeByte(pix.blue, bitsPerPixel);
    }
    writer.close();
}

std::vector<pixel> BitFiles::retrieveImage(const char* filename, uint8_t& levelsResult, uint64_t& resultSize, TGAHeader* header) {

    BitReader reader;
    reader.open(filename);

    auto readByte = [&reader](uint8_t bitsPerPixel) -> uint8_t {
        uint8_t result = 0;

        for (size_t i = 0; i < bitsPerPixel; i++) {
            result = (result << 1) + reader.getBit() ? 1 : 0;
        }

        return result;
    };

    uint8_t headerCopy[sizeof(*header)];

    for (size_t i = 0; i < sizeof(*header); i++) {
        headerCopy[i] = readByte(8);
    }

    memcpy(header, headerCopy, sizeof(*header));

    uint8_t bitsPerPixel = readByte(8);
    uint64_t uncompressedSize = 0;
    uint8_t tempBytes[8];

    for (size_t i = 0; i < 8; i++) {
        tempBytes[i] = readByte(8);
    }
    std::memcpy(&uncompressedSize, tempBytes, sizeof(uncompressedSize));

    resultSize = uncompressedSize;
    levelsResult = bitsPerPixel;

    std::vector<pixel> result;

    for (size_t i = 0; i < uncompressedSize; i++) {
        result.push_back((pixel){readByte(bitsPerPixel), readByte(bitsPerPixel), readByte(bitsPerPixel)});
    }

    reader.close();

    return result;
}