
#ifndef source_h
#define source_h

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "image.h"
using std::endl;
using std::cout;


class Source
{
protected:
    Image img;
    virtual void Execute() = 0;

public:
    // Pure virtual function
    Image* GetOutput();
    virtual void Update() = 0;
    virtual const char * Name()=0;
};
#endif /* source_h */
