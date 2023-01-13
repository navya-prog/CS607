//
//  PNMReader.h
//  3C
//
//  Created by Navya Daggubati on 11/26/22.
//

#include "PNMreader.h"
#include <cstring>

PNMreader::PNMreader(char *fn_input)
{
    //this->filename = new char[strlen(fn_input) + 1];
    strcpy(this->filename, fn_input);
    std::cout << "reader construct" << std::endl;
    img.setSource(this);
}

/*
PNMreader::~PNMreader()
{
    delete(this->filename);
    std::cout << "reader destruct" << std::endl;
}*/

void PNMreader::Update()
{
    Execute();
}

void PNMreader::Execute()
{
    std::cout << "reader execute1" << std::endl;
    char magicnum[128];
    int width, height, maxval;
    FILE *f_in;
    std::cout << filename << std::endl;
    f_in = fopen(filename, "r");
    std::cout << "reader execute1.1" << std::endl;
    fscanf(f_in, "%s\n%d %d\n%d\n", magicnum, &width, &height, &maxval);

    std::cout << "reader execute2" << std::endl;

    img.setImage(width, height);

    std::cout << "reader execute3 " << std::endl;

    int i = 0;
    Pixel ptemp;

    for (i = 0; i < img.getWidth() * img.getHeight(); i++)
    {
        fscanf(f_in, "%c%c%c", &ptemp.r, &ptemp.g, &ptemp.b);
        img.getImagePixel()[i] = ptemp;
    }

    std::cout << "reader execute4" << std::endl;
    fclose(f_in);
}
