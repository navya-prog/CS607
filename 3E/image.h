//
//  image.h
//  3B
//
//  Created by Navya Daggubati
//

#ifndef image_h
#define image_h
//#include "source.h"

class Source;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;


class Image
{
private:
    Pixel *pixel;
    int width, height, maxval;
    Source *source;
public:
    char * magicNum;
    int getWidth();
    int getHeight();
    int getMaxVal();
    Pixel* getImagePixel();
    int GetNumberofPixels() const;
    void setImage(int width, int height);
    void setSource(Source *src);
    void Free();
    void Clean();
    void Update();
};

#endif /* image_h */
