//
//  main3B.c
//  3B solution
//
//  Created by Navya Daggubati
//
#include "image.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadImage(char *filename, Image *img)
{
    FILE *f_in;
    char magicnum[128];
    int width, height, maxval;
    f_in = fopen(filename, "r");
    fscanf(f_in, "%s\n%d %d\n%d\n", magicnum, &width, &height, &maxval);

    img->pixel = (Pixel *)malloc(width*height*sizeof(Pixel));
    img->magicNum = magicnum;
    img->width = width;
    img->height = height;
    img->maxval = maxval;
    
    int i=0;
    Pixel ptemp;
    
    for(i=0; i<img->width*img->height; i++){
        fscanf(f_in, "%c%c%c", &ptemp.r, &ptemp.g, &ptemp.b);
        img->pixel[i] = ptemp;
    }
    
    fclose(f_in);
}

void HalfSize(Image *input, Image *output)
{
    // half size, skip alternate rows and columns
    // half width, half height
    int w, h, i,j,k;
    w = input->width;
    h = input->height;
    
    output->width = w/2;
    output->height = h/2;
    output->magicNum = input->magicNum;
    output->pixel = (Pixel *) malloc(w*h*0.25*sizeof(Pixel)); //half height, half width
    output->maxval = input->maxval;
    
    i=0; j =0; k=0;
    for(j=0; j<h; j++)
    {
        for(i=0;i<w;i++)
        {
            output->pixel[k] = input->pixel[j*w + i];
            i = i+1; //skip alternate pixels
            k=k+1;
        }
        j = j+1; //skip alternate rows
    }
}


void LeftRightCombine(Image *leftIm, Image *rightIm, Image *output)
{
    
    int i, j, k, lw, lh, rw, rh;
    lw = leftIm->width;
    lh = leftIm->height;
    
    rw = rightIm->width;
    rh = rightIm->height;
    
    output->width = lw + rw; //sum of width of both images
    output->height = lh; //should be same as rh
    output->magicNum = leftIm->magicNum;
    output->maxval = leftIm->maxval;
    output->pixel = (Pixel *)malloc(output->width*output->height*sizeof(Pixel));
    
    k=0;
    for(j=0; j<lh; j++)
    {
        for(i=0;i<lw;i++)
        {
            output->pixel[k] = leftIm->pixel[j*lw + i];
            k=k+1;
        }
        // join each row from right Image
        for(i=0;i<rw;i++)
        {
            output->pixel[k] = rightIm->pixel[j*rw + i];
            k=k+1;
        }
    }
}

void TopBottomCombine(Image *topIm, Image *bottomIm, Image *output)
{
    
    int i, j, k, tw, th, bw, bh;
    tw = topIm->width;
    th = topIm->height;
    
    bw = bottomIm->width;
    bh = bottomIm->height;
    
    output->width = tw; //should be same as rw
    output->height = th + bh; //sum of heights
    output->magicNum = topIm->magicNum;
    output->maxval = topIm->maxval;
    output->pixel = (Pixel *)malloc(output->width*output->height*sizeof(Pixel));
    
    k=0;
    for(j=0; j<th; j++)
    {
        for(i=0;i<tw;i++)
        {
            output->pixel[k] = topIm->pixel[j*tw + i];
            k=k+1;
        }
    }

    // join image again on height
    for(j=th; j<th+bh; j++)
    {
        for(i=0;i<bw;i++)
        {
            output->pixel[k] = bottomIm->pixel[(j-th)*bw + i];
            k=k+1;
        }
    }
}


void Blend(Image *input1, Image *input2, double factor, Image *output)
{
    int i, j, k, w1, h1, w2, h2;
    w1 = input1->width;
    h1 = input1->height;
    
    w2 = input2->width;
    h2 = input2->height;
    
    output->width = w1;
    output->height = h1;
    output->magicNum = input1->magicNum;
    output->maxval = input1->maxval;
    output->pixel = (Pixel *)malloc(output->width*output->height*sizeof(Pixel));
    
    k=0;
    for(j=0; j<h1; j++)
    {
        for(i=0;i<w1;i++)
        {
            output->pixel[k].r = (factor)*(input1->pixel[j*w1 + i].r)  + (1-factor)*input2->pixel[j*w1 + i].r;
            output->pixel[k].g = (factor)*(input1->pixel[j*w1 + i].g)  + (1-factor)*input2->pixel[j*w1 + i].g;
            output->pixel[k].b = (factor)*(input1->pixel[j*w1 + i].b)  + (1-factor)*input2->pixel[j*w1 + i].b;
            k=k+1;
        }
    }
}


void WriteImage(char *filename, Image *img)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    int i;
    
    fprintf(f_out, "%s\n%d %d\n%d\n", "P6", img->width, img->height, img->maxval);
    for(i=0; i<img->width*img->height; i++){
        fprintf(f_out, "%c%c%c", img->pixel[i].r, img->pixel[i].g, img->pixel[i].b);
    }
    fclose(f_out);
}


int main(int argc, char *argv[])
{
    Image img, img2, img3, img4, img5, img6, img7, img8;
    ReadImage(argv[1], &img);
    
    HalfSize(&img, &img2);
    LeftRightCombine(&img2, &img2, &img3);
    TopBottomCombine(&img3, &img3, &img4);
    HalfSize(&img4, &img5);
    LeftRightCombine(&img5, &img2, &img6);
    TopBottomCombine(&img6, &img3, &img7);
    Blend(&img7, &img, 0.795, &img8);
    WriteImage(argv[2], &img8);
}