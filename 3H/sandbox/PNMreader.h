#ifndef PNMreader_h
#define PNMreader_h
#include "image.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "source.h"
#include <string>
#include <logging.h>

class PNMreader: public Source 
{
private:
    char * filename;
    const char * class_name = "PNMreader";

protected:
    void Execute();

public:
    PNMreader(char *fn_input);
    //~PNMreader();
    void Update();
    const char* Name();
    
};
#endif /* PNMReader_h */
