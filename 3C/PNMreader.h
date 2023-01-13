//
//  PNMReader.h
//  3C
//
//  Created by Navya Daggubati on 11/26/22.
//

#ifndef PNMreader_h
#define PNMreader_h
#include "image.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "source.h"

class PNMreader: public Source 
{
private:
    char * filename;

public:
    PNMreader(char *fn_input);
    ~PNMreader();
    void Execute();
    Image * GetOutput();
};
#endif /* PNMReader_h */
