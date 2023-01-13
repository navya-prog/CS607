//
//  source.h
//  3C
//
//  Created by Navya Daggubati
//

#ifndef source_h
#define source_h

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "image.h"

class Source
{
protected:
    Image img;
public:
    // Pure virtual function
    virtual void Execute() = 0;
    Image* GetOutput();
};
#endif /* source_h */
