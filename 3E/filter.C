//
//  filter.c
//  3C
//
//  Created by Navya Daggubati
//

#include "filter.h"
#include <iostream>
using std::endl;
using std::cout;


Filter::Filter()
{
    img.setSource(this);
}

void Filter::Update()
{
    if (img1) {
        cout << "in img1 update" << endl;
        img1->Update();
        cout << "img1 completed" << endl;

    }

    if (img2) {
        cout << "in img2 update" << endl;
        img2->Update();
        cout << "img2 completed" << endl;
    }

    cout << "execution starting" << endl;
    Execute();
    cout << "execution completed" << endl;
    
    if(img1){
        cout << "inside img1 freeing" << endl;
        img1->Clean();
    }
    
    if(img2){
        cout << "inside img2 freeing" << endl;
        img2->Clean();
        
    }
}

void Blender::SetFactor(double f)
{
    this->factor = f;
}

void Blender::Execute()
{
    int i, j, k, w1, h1, w2, h2;
    Pixel *input, *input2;
    w1 = img1->getWidth();
    h1 = img1->getHeight();

    w2 = img2->getWidth();
    h2 = img2->getHeight();

    
    this->img.setImage(w1, h1);

    k = 0;
    for (j = 0; j < h1; j++) {
        for (i = 0; i < w1; i++) {
            img.getImagePixel()[k].r = (factor) * (img1->getImagePixel()[j * w1 + i].r) + (1 - factor) * img2->getImagePixel()[j * w1 + i].r;
            img.getImagePixel()[k].g = (factor) * (img1->getImagePixel()[j * w1 + i].g) + (1 - factor) * img2->getImagePixel()[j * w1 + i].g;
            img.getImagePixel()[k].b = (factor) * (img1->getImagePixel()[j * w1 + i].b) + (1 - factor) * img2->getImagePixel()[j * w1 + i].b;
            k = k + 1;
        }
    }
}

void LRCombine::Execute()
{
    int i, j, k, lw, lh, rw, rh;
    lw = img1->getWidth();
    lh = img1->getHeight();

    rw = img2->getWidth();
    rh = img2->getHeight();

    img.setImage(lw + rw, lh); // sum of width of both images & lh

    k = 0;
    for (j = 0; j < lh; j++)
    {
        for (i = 0; i < lw; i++)
        {
            img.getImagePixel()[k] = img1->getImagePixel()[j * lw + i];
            k = k + 1;
        }
        // join each row from right Image
        for (i = 0; i < rw; i++)
        {
            img.getImagePixel()[k] = img2->getImagePixel()[j * rw + i];
            k = k + 1;
        }
    }
}

void TBCombine::Execute()
{
    int i, j, k, tw, th, bw, bh;
    tw = img1->getWidth();
    th = img1->getHeight();

    bw = img2->getWidth();
    bh = img2->getHeight();

    img.setImage(tw, th + bh); // should be same as tw & sum of heights

    k = 0;
    for (j = 0; j < th; j++)
    {
        for (i = 0; i < tw; i++)
        {
            img.getImagePixel()[k] = img1->getImagePixel()[j * tw + i];
            k = k + 1;
        }
    }

    // join image again on height
    for (j = th; j < th + bh; j++)
    {
        for (i = 0; i < bw; i++)
        {
            img.getImagePixel()[k] = img2->getImagePixel()[(j - th) * bw + i];
            k = k + 1;
        }
    }
}

void Shrinker::Execute()
{
    int w, h, i, j, k;
    w = this->img1->getWidth();
    h = this->img1->getHeight();

    img.setImage(w/2, h/2);

    i = 0;
    j = 0;
    k = 0;
    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            img.getImagePixel()[k] = img1->getImagePixel()[j * w + i];
            i = i + 1; // skip alternate pixels
            k = k + 1;
        }
        j = j + 1; // skip alternate rows
    }
}
