#include <cstring>
#include <cstdlib>
#include "TgaAdapter.hpp"

bool TgaAdapter::openFile(const char* filename) {
    
    //Otwieramy plik tga
    tga = TGAOpen(filename, "r");
    if (!tga || tga->last != TGA_OK) {
        perror("opening error\n");
        return false;
    }
    
    //Wczytujemy dane
    data.flags = TGA_IMAGE_DATA | TGA_IMAGE_ID | TGA_RGB;
	if(TGAReadImage(tga, & data) != TGA_OK) {
	    perror("parsing error\n");
        return false;
	}
    
    width = tga->hdr.width;
    height = tga->hdr.height;
    
    if (tga->hdr.depth != 24 && tga->hdr.map_t != 0 && tga->hdr.alpha > 0) {
        perror("The image does not meets requierd conditions:\n"
                "- there must not be a color map\n"
                "- alpha must be 0 bytes long\n"
                "- depth must be 24 bits (8 per color)\n");
                return false;
    }

    size_t counter = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            pixel temp = {0,0,0};
            temp.red = (uint8_t) data.img_data[counter++];
            temp.green = (uint8_t) data.img_data[counter++];
            temp.blue = (uint8_t) data.img_data[counter++];
            image.push_back(temp);
        }
    }
    return true;
}

std::vector<pixel> TgaAdapter::retrieve() {
    return image;
}

bool TgaAdapter::persistCopy(std::vector<pixel> imageCopy, const char* filename) {
    
    //Otwieramy plik wyjscia
    TGA* output = TGAOpen(filename, "w");
    if (!output || output->last != TGA_OK) {
        TGAClose(tga);
        perror("opening error\n");
        return false;
    }

    memcpy(&(output->hdr), &(tga->hdr), sizeof(tga->hdr));
    size_t counter = 0;

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            data.img_data[counter++] = imageCopy[i * width + j].red;
            data.img_data[counter++] = imageCopy[i * width + j].green;
            data.img_data[counter++] = imageCopy[i * width + j].blue;
        }
    }
    
    TGAWriteImage(output, &data);
    TGAClose(output);
    
    return true;
}

void TgaAdapter::closeFile() {
    free(data.img_data);
    free(data.cmap);
    free(data.img_id);
    TGAClose(tga);
}