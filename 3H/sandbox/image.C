#include "image.h"
#include "source.h"
#include <iostream>

using std::endl;
using std::cout;


int Image::GetNumberofPixels() const
{
    return width * height;
}

int Image::getWidth()
{
    return this->width;
}

int Image::getHeight()
{
    return this->height;
}

int Image::getMaxVal()
{
    return this->maxval;
}


Pixel* Image::getImagePixel()
{
    return this->pixel;
}

void Image::setImage(int width, int height)
{
    this->pixel = new Pixel[width * height];
    this->width = width;
    this->height = height;
    this->maxval = 255;
}


void Image::setSource(Source *src)
{
    this->source = src;
}


void Image::Update()
{
    if (this->source)
    {
        this->source->Update();
    }
}


/*
 void Image::Free()
 {
 cout<<"inside Image Free"<<endl;
 if (this->pixel !=0)
 {
 cout<<"inside image pixel Free"<<endl;
 delete(this->pixel);
 this->pixel = 0;
 }
 
 if (this->source)
 {
 cout<<"inside source Free"<<endl;
 this->source->Free();
 }
 
 }
 */
