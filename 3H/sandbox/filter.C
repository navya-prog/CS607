//
//  filter.c
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
        //cout << "In Img1 update" << endl;
        sprintf(msg, "%s: about to update input1", this->Name());
        Logger::LogEvent(msg);

        img1->Update();
        sprintf(msg, "%s: done updating input1", this->Name());
        Logger::LogEvent(msg);
    }

    if (img2)
    {
        //cout << "In Img2 update" << endl;
        sprintf(msg, "%s: about to update input2", this->Name());
        Logger::LogEvent(msg);
        
        img2->Update();
        sprintf(msg, "%s: done updating input2", this->Name());
        Logger::LogEvent(msg);
    }
    
    //cout << "Image update about to execute" << endl;
    sprintf(msg, "%s: about to execute", this->Name());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", this->Name());
    //cout << "Image update done executing" << endl;
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
    
    if ((w1 != w2) || (h1 != h2))
    {
        char msg[100];
        sprintf(msg, "%s: image dimensions must match (%d, %d) and (%d, %d)", Name(), w1, w2, h1, h2);
        DataFlowException e(Name(), msg);
        throw e;
    }

    k = 0;
    double f = this->factor;
    for (j = 0; j < h1; j++) {
        for (i = 0; i < w1; i++) {
            img.getImagePixel()[k].r = ((f) * (img1->getImagePixel()[j * w1 + i].r)) + ((1 - f) * img2->getImagePixel()[j * w1 + i].r);
            img.getImagePixel()[k].g = ((f) * (img1->getImagePixel()[j * w1 + i].g)) + ((1 - f) * img2->getImagePixel()[j * w1 + i].g);
            img.getImagePixel()[k].b = ((f) * (img1->getImagePixel()[j * w1 + i].b)) + ((1 - f) * img2->getImagePixel()[j * w1 + i].b);
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

    i = 0; j = 0; k = 0;


    for (j = 0; j < 2*(h/2); j++)
    {
        for (i = 0; i < 2*(w/2); i++)
        {
            img.getImagePixel()[k] = img1->getImagePixel()[j*w + i];
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
const char * Mirror::Name() { return this->class_name;}
const char * Rotate::Name() { return this->class_name;}
const char * Subtract::Name() { return this->class_name;}
const char * Grayscale::Name() { return this->class_name;}
const char * Blur::Name() { return this->class_name;}
const char * Color::Name() { return this->class_name;}
const char * CheckSum::Name() { return this->class_name;}

void Mirror::Execute()
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
    img.setImage(w, h);
    k = 0;
    
    for (j = 0; j < h; j++)
    {
        for (i = w-1; i >= 0; i--) //flip columns, last becomes first in new image,
        {
            img.getImagePixel()[k] = img1->getImagePixel()[j * w + i];
            k = k + 1;
        }
    }
}

void Grayscale::Execute()
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

    img.setImage(w, h);

    i = 0;j = 0; k = 0;
    Pixel temp, pixel;
    int gs_value;
    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++) //
        {
            temp = img1->getImagePixel()[j * w + i];
            gs_value = (int)temp.r/5 + (int)temp.g/2 + (int)temp.b/4 ; //integer divison
            pixel.r = gs_value; pixel.g = gs_value; pixel.b = gs_value;
            img.getImagePixel()[k] = pixel;
            k = k + 1;
        }
    }
}


void Blur::Execute()
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
    img.setImage(w, h);

    k = 0;
    Pixel temp, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    //cout << "Blur execute - about to loop" << endl;

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++) //
        {
            // first row, first column, last column, last row copy as is.
            //blur not applied since they are on boundary.
            if ((i==0)|| (j==0) || (i==w-1) || (j==h-1)) {
                img.getImagePixel()[k] = img1->getImagePixel()[j * w + i];
            }
            else {
            // average of 8 pixels around it
                temp1 = img1->getImagePixel()[(j-1) * w + i];
                temp2 = img1->getImagePixel()[(j-1) * w + i-1];
                temp3 = img1->getImagePixel()[(j-1) * w + i+1];
                temp4 = img1->getImagePixel()[j * w + i-1];
                temp5 = img1->getImagePixel()[j * w + i+1];
                temp6 = img1->getImagePixel()[(j+1) * w + i];
                temp7 = img1->getImagePixel()[(j+1) * w + i-1];
                temp8 = img1->getImagePixel()[(j+1) * w + i+1];
                temp.r = temp1.r/8 +temp2.r/8 + temp3.r/8 + temp4.r/8 + temp5.r/8 + temp6.r/8 + temp7.r/8 + temp8.r/8;
                temp.g = temp1.g/8 +temp2.g/8 + temp3.g/8 + temp4.g/8 + temp5.g/8 + temp6.g/8 + temp7.g/8 + temp8.g/8;
                temp.b = temp1.b/8 +temp2.b/8 + temp3.b/8 + temp4.b/8 + temp5.b/8 + temp6.b/8 + temp7.b/8 + temp8.b/8;
                img.getImagePixel()[k] = temp;
            }
            k = k + 1;
        }
    }
}


void Subtract::Execute()
{
    int i, j, k, w1, w2, h1, h2;
    
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
    
    w1 = img1->getWidth();
    h1 = img1->getHeight();

    w2 = img2->getWidth();
    h2 = img2->getHeight();

    if ((w1 != w2) || (h1 != h2))
    {
        char msg[100];
        sprintf(msg, "%s: height and width must match: (%d, %d), (%d, %d)", Name(), w1, h1, w2, h2);
        cout << "exception in height width check" << endl;
        DataFlowException e(Name(), msg);
        throw e;
    }
    
    img.setImage(w1, h1); // should be same as tw & sum of heights

    Pixel p1, p2, p;
    k = 0;
    for (j = 0; j < h1; j++)
    {
        for (i = 0; i < w1; i++)
        {
            p1 =img1->getImagePixel()[j * w1 + i];
            p2 =img2->getImagePixel()[j * w1 + i];
            
            if (p1.r > p2.r) {p.r = p1.r - p2.r;}
            else {p.r = 0;}
            
            if (p1.g > p2.g) {p.g = p1.g - p2.g;}
            else {p.g = 0;}
            
            if (p1.b > p2.b) {p.b = p1.b - p2.b;}
            else {p.b = 0;}
            
            img.getImagePixel()[k] = p;
            k = k + 1;
        }
    }
}

void Rotate::Execute()
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
    
    w = img1->getWidth();
    h = img1->getHeight();
    img.setImage(h, w);

    i = 0; j = 0; k = 0;
    for (i = 0; i<w; i++)
    {
        for (j = h-1; j >=0; j--)
        {
            img.getImagePixel()[k] = img1->getImagePixel()[j*w + i];
            k = k + 1;
        }
    }
}


void Color::Execute()
{
    img.setImage(width, height);
    int i;
    
    for (i = 0; i < height * width; i++)
    {
        img.getImagePixel()[i].r = r;
        img.getImagePixel()[i].g = g;
        img.getImagePixel()[i].b = b;
    }
}


void CheckSum::OutputCheckSum(const char* file)
{
    FILE *f_in;
    Pixel *temp;
    int i;

    if (!img1)
    {
        char msg[128];
        sprintf(msg, "%s: no input1!", Name());
        DataFlowException e(Name(), msg);
        throw e;
    }

    int width, height;
    unsigned char r = 0, g = 0, b = 0;
    temp = img1->getImagePixel();
    width = img1->getWidth();
    height = img1->getHeight();

    //calculate checksum
    for (i = 0; i < width * height; i++)
    {
        r += img1->getImagePixel()[i].r;
        g += img1->getImagePixel()[i].g;
        b += img1->getImagePixel()[i].b;
    }

    //read file with read binary mode
    f_in = fopen(file, "w");

    //write checksum
    fprintf(f_in, "CHECKSUM: %d, %d, %d\n", r, g, b);

    //close file
    fclose(f_in);
}
