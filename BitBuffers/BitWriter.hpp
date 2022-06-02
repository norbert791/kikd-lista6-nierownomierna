#pragma once
#include<string>
#include<fstream>

class BitWriter {
    public:
        BitWriter() = default;
        BitWriter(const std::string& outputName);
        void writeBit(const bool input);
        void open(const std::string& outputName);
        void close();
        size_t getBytesWrote();
        ~BitWriter();

    private:
        unsigned char buffer = 0;
        unsigned char bufferCounter = 0;
        const static uint32_t msbMask = 0x80000000;//0x80000000;
        size_t bytesWrote = 0;
        std::ofstream output;
};

