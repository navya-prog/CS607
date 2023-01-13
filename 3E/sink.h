//
//  sink.h
//  3C
//
//  Created by Navya Daggubati
//

#ifndef sink_h
#define sink_h
#include "image.h"

class Sink
{
    protected:
    Image *img1, *img2;

    public:
    void SetInput(Image *input);
    void SetInput2(Image *input);
};


#endif /* sink_h */
