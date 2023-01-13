//
//  PNMWriter.h
//  3C
//
//  Created by Navya Daggubati on 11/26/22.
//

#ifndef PNMwriter_h
#define PNMwriter_h
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "image.h"
#include "sink.h"

class PNMwriter: public Sink
{
private:
    Image *img;
public:
    void SetInput(Image *img);
    void Write(char * filename);
};


#endif /* PNMWriter_h */
