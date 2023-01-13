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


class Mirror : public Filter
{
private:
    const char * class_name = "Mirror";
protected:
    void Execute();
public:
    const char* Name();
};


class Rotate : public Filter
{
private:
    const char * class_name = "Rotate";
protected:
    void Execute();
public:
    const char* Name();
};


class Subtract : public Filter
{
private:
    const char * class_name = "Subtract";
protected:
    void Execute();
public:
    const char* Name();
};

class Grayscale : public Filter
{
private:
    const char * class_name = "Grayscale";
protected:
    void Execute();
public:
    const char* Name();
};

class Blur : public Filter
{
private:
    const char * class_name = "blue";
protected:
    void Execute();
public:
    const char* Name();
};

class Color : public Filter
{
private:
    const char * class_name = "Color";
    int r, g, b, width, height;
public:
    Color(int width, int height, int r, int g, int b){
        this->r = r;
        this->g = g;
        this->b = b;
        this->width = width;
        this->height= height; 
    };
    const char* Name();
protected:
    void Execute();
};

class CheckSum : public Sink
{
private:
    const char * class_name = "CheckSum";
public:
    const char* Name();
    void OutputCheckSum(const char* file);
};

#endif /* filter_h */

