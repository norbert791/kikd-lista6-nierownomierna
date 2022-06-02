#include "BitWriter.hpp"
#include <string>
#include <iostream>

using uc = unsigned char;

BitWriter::BitWriter(const std::string& outputName) {
        output = std::ofstream(outputName);
        if (!output.good()) {
            throw std::logic_error("IO exception");
        }
    }

void BitWriter::writeBit(const bool input) {
   // std::cout<<input<<std::endl;
    buffer = (unsigned char)(buffer<<1);
    buffer += input ? 1 : 0;
    bufferCounter++;
    if (bufferCounter == 8) {
        bufferCounter = 0;
        bytesWrote++;
        output.put(buffer);
        buffer = 0;
    }
}

BitWriter::~BitWriter() {
    if (bufferCounter > 0) {
        while (bufferCounter < 8) {
            buffer = (uc)(buffer << 1);
            bufferCounter++;
        }
        bytesWrote++;
        output.put(buffer);
    }
    output.close();
}

void BitWriter::open(const std::string& filename) {
    if (output.is_open()) {
        output.close();
    }
    output = std::ofstream(filename);
    if (!output.good()) {
        throw std::logic_error("IO exception");
    }
    bytesWrote = 0;
}

void BitWriter::close() {
    if (bufferCounter > 0) {
        while (bufferCounter < 8) {
            buffer = (uc)(buffer << 1);
            bufferCounter++;
        }
        bytesWrote++;
        output.put(buffer);
    }
    output.close();
}

size_t BitWriter::getBytesWrote() {
    return bytesWrote;
}