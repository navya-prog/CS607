//
//  PNMWriter.c
//  3C
//
//  Created by Navya Daggubati on 11/26/22.
//

#include "PNMwriter.h"

void PNMwriter::SetInput(Image *img) {
        this->img = img;
        std::cout << "writer setInput"<<std::endl;
}

void PNMwriter::Write(char *filename)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    int i;
    std::cout << filename << std::endl;
    std::cout << "writer execute2" << std::endl;

    fprintf(f_out, "%s\n%d %d\n%d\n", "P6", this->img->getWidth(), this->img->getHeight(), this->img->getMaxVal());
    std::cout << "writer execute3" << std::endl;
    for (i = 0; i < this->img->getWidth() * this->img->getHeight(); i++)
    {
        fprintf(f_out, "%c%c%c", this->img->getImagePixel()[i].r, this->img->getImagePixel()[i].g, this->img->getImagePixel()[i].b);
    }
    fclose(f_out);
    //img->ImageFree();
    img->Free();
    std::cout << "writer execute4" << std::endl;
}
