//
//  image.h
//  3B
//
//  Created by Navya Daggubati
//
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

    if (this->pixel){
	    delete(this->pixel);
    }
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
        this->source->Update();
}


void Image::Free(){
     if(this->pixel){
	 delete(this->pixel);
	 this->pixel = 0;
     }
}

void Image::Clean()
{
    if (this->source)
    {
        cout <<"freeing source data" << endl;
        cout << this->source << endl;
        this->source->Clean();
        cout <<"succesfully cleared pixel data" << endl;
    }
}
