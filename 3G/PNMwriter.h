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
#include "string"
#include <logging.h>

class PNMwriter: public Sink
{
private:
    Image *img;
    const char * class_name = "PNMwriter";
public:
    void SetInput(Image *img);
    void Write(char * filename);
    const char* Name();
};


#endif /* PNMWriter_h */
