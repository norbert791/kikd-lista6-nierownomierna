#ifndef ID_QUANTIZER_HPP
#define ID_QUANTIZER_HPP

#include <vector>
#include "FilterQuantizer.hpp"

class IdQuantizer : public FilterQuantizer{

    public:
        IdQuantizer() = default;
        signedPixel assignQuant(signedPixel pix) override;
        signedPixel getQuantVector(signedPixel pix) override;
        std::vector<signedPixel> mapToIndexes(const std::vector<signedPixel>& image) override;
        ~IdQuantizer() =  default;
};


#endif