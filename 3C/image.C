//
//  image.h
//  3B
//
//  Created by Navya Daggubati
//
#include "image.h"

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

Image::~Image()
{
    delete(this->pixel);
}