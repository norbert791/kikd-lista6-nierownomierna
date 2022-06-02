#pragma once
#include<string>
#include<fstream>

using uc = unsigned char;

class BitReader {
    public:
        BitReader() = default;
        BitReader(const std::string& inputName);
        ~BitReader();
        bool getBit();
        void open(const std::string& filename);
        void close();
        bool good();
    private:
        uc buffer = 0;
        uc bufferCounter = 0;
        const static uc msbMask = 128; 
        std::ifstream input;
};