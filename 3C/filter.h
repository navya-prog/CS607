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

class Filter : public Source, public Sink
{
};

class Blender : public Filter
{
private:
    double factor;

public:
    void SetFactor(double f);
    void Execute();
};

class Shrinker : public Filter
{
public:
    void Execute();
};

class LRCombine : public Filter
{
public:
    void Execute();
};

class TBCombine : public Filter
{
public:
    void Execute();
};

#endif /* filter_h */
