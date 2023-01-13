//
//  filter.c
//  3C
//
//  Created by Navya Daggubati
//

#include "filter.h"
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

Filter::Filter()
{
    img1 = 0;
    img2 = 0;
    img.setSource(this);
}

void Filter::Update()
{
    char msg[100];

    if (img1)
    {
        sprintf(msg, "%s: about to update input1", this->Name());
        Logger::LogEvent(msg);

        img1->Update();
        sprintf(msg, "%s: done updating input1", this->Name());
        Logger::LogEvent(msg);
    }

    if (img2)
    {
        sprintf(msg, "%s: about to update input2", this->Name());
        Logger::LogEvent(msg);
        
        img2->Update();
        sprintf(msg, "%s: done updating input2", this->Name());
        Logger::LogEvent(msg);
    }
    
    sprintf(msg, "%s: about to execute", this->Name());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", this->Name());
    Logger::LogEvent(msg);

}

void Blender::SetFactor(double f){this->factor = f;}

void Blender::Execute()
{
    int i, j, k, w1, h1, w2, h2;
    Pixel *input, *input2;
    
    //check for exceptions
    if (!img1)
    {
        char msg[100];
        sprintf(msg, "%s: input1 not provided!", Name());
        cout << "exception in input check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }

    if (!img2)
    {
        char msg[100];
        sprintf(msg, "%s: input2 not provided!", Name());
        cout << "exception in input check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }
    
    if (this->factor > 1.0)
    {
        cout << "exception in blending factor" << endl;
        char msg[100];
        sprintf(msg, "%s: blending factor cannot be >1: %f", Name(), this->factor);
        DataFlowException e(Name(), msg);
        throw e;
    }

    
    w1 = img1->getWidth();
    h1 = img1->getHeight();

    w2 = img2->getWidth();
    h2 = img2->getHeight();
    this->img.setImage(w1, h1);
    
    if ((w1 != w2) && (h1 != h2))
    {
        char msg[100];
        sprintf(msg, "%s: image dimensions must match (%d, %d) and (%d, %d)", Name(), w1, w2, h1, h2);
        DataFlowException e(Name(), msg);
        throw e;
    }

    k = 0;
    int f = this->factor;
    for (j = 0; j < h1; j++) {
        for (i = 0; i < w1; i++) {
            img.getImagePixel()[k].r = (f) * (img1->getImagePixel()[j * w1 + i].r) + (1 - f) * img2->getImagePixel()[j * w1 + i].r;
            img.getImagePixel()[k].g = (f) * (img1->getImagePixel()[j * w1 + i].g) + (1 - f) * img2->getImagePixel()[j * w1 + i].g;
            img.getImagePixel()[k].b = (f) * (img1->getImagePixel()[j * w1 + i].b) + (1 - f) * img2->getImagePixel()[j * w1 + i].b;
            k = k + 1;
        }
    }
}

void LRCombine::Execute()
{
    int i, j, k, lw, lh, rw, rh;
    
    //check for exceptions
    if (!img1)
    {
        char msg[100];
        sprintf(msg, "%s: input1 not provided!", Name());
        cout << "exception in input check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }

    if (!img2)
    {
        char msg[100];
        sprintf(msg, "%s: input2 not provided!", Name());
        cout << "exception in input check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }
    
    lw = img1->getWidth();
    lh = img1->getHeight();

    rw = img2->getWidth();
    rh = img2->getHeight();

    if (lh != rh)
    {
        char msg[100];
        sprintf(msg, "%s: heights must match: %d, %d", Name(), lh, rh);
        cout << "exception in height check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }

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
    
    //check for exceptions
    if (!img1)
    {
        char msg[100];
        sprintf(msg, "%s: input1 not provided!", Name());
        cout << "exception in input check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }

    if (!img2)
    {
        char msg[100];
        sprintf(msg, "%s: input2 not provided!", Name());
        cout << "exception in input check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }
    
    tw = img1->getWidth();
    th = img1->getHeight();

    bw = img2->getWidth();
    bh = img2->getHeight();

    if (tw != bw)
    {
        char msg[100];
        sprintf(msg, "%s: width must match: %d, %d", Name(), tw, bw);
        cout << "exception in width check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }
    
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
    
    //check for exceptions
    if (!img1)
    {
        char msg[100];
        sprintf(msg, "%s: input1 not provided!", Name());
        DataFlowException e(Name(), msg);
        throw e;
    }
    
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


const char * Shrinker::Name() { return this->class_name;}
const char * Blender::Name() { return this->class_name;}
const char * TBCombine::Name() { return this->class_name;}
const char * LRCombine::Name() { return this->class_name;}

