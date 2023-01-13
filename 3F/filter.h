//
//  filter.h
//  3C
//
//  Created by Navya Daggubati
//

#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include "image.h"
#include "sink.h"
#include "source.h"
#include <string>
#include <logging.h>

class Filter : public Source, public Sink
{
public:
    Filter();
    void Update();
};

class Blender : public Filter
{
    
private:
    double factor;
    const char * class_name = "Blender";

protected:
    void Execute();

public:
    void SetFactor(double f);
    const char* Name();
};

class Shrinker : public Filter
{
    
private:
    const char * class_name = "Shrinker";

protected:
    void Execute();
public:
    const char* Name();
};

class LRCombine : public Filter
{
private:
    const char * class_name = "LRCombine";
protected:
    void Execute();

public:
    const char* Name();
};

class TBCombine : public Filter
{
private:
    const char * class_name = "TBCombine";
    
protected:
    void Execute();
public:
    const char* Name();
};

#endif /* filter_h */
