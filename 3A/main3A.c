#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct
{
    char * magicNum;
    int width;
    int height;
    int maxval;
    Pixel *pixel;
} Image;


Image * ReadImage(char *filename)
{
    FILE *f_in;
    char magicnum[128];
    int width, height, maxval;
    f_in = fopen(filename, "r");
    fscanf(f_in, "%s\n%d %d\n%d\n", magicnum, &width, &height, &maxval);

    Image *img;
    img = malloc(sizeof(Image));
    img->pixel = malloc(width*height*sizeof(Pixel));

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
    return img;
}


void WriteImage(Image *img, char *filename)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    char * s_temp;
    int i;
    
    fprintf(f_out, "%s\n%d %d\n%d\n", "P6", img->width, img->height, img->maxval);
    for(i=0; i<img->width*img->height; i++){
        fprintf(f_out, "%c%c%c", img->pixel[i].r, img->pixel[i].g, img->pixel[i].b);
    }
    fclose(f_out);
}

Image * YellowDiagonal(Image *input)
{
    int w, h, i, smaller;
    w = input->width;
    h = input->height;
    
    if(w>h){
        smaller = h;
    }
    else{
        smaller = w;
        }
    
    for(i=0;i<smaller; i++){
        input->pixel[i*w + i].r = 255;
        input->pixel[i*w + i].g = 255;
        input->pixel[i*w + i].b = 0;
    }
    
    return input;
}

int main(int argc, char *argv[])
{
    /* Read an image, apply yellow diagonal to it, then write */
    Image *img;
    img = ReadImage(argv[1]);
    img = YellowDiagonal(img);
    WriteImage(img, "3A_output.pnm");
    
}