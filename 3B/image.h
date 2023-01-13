//
//  image.h
//  3B
//
//  Created by Navya Daggubati
//

#ifndef image_h
#define image_h

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


#endif /* image_h */
