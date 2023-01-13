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
    virtual void Execute() = 0;

public:
    // Pure virtual function
    Image* GetOutput();
    virtual void Update() = 0;  //run update operation
    void Clean(){
	    img.Free();
        }
};
#endif /* source_h */
