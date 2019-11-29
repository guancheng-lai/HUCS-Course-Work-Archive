//
//  Picture.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/9/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Picture_hpp
#define Picture_hpp
#include "RGBTriple.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
using std::ofstream;
using std::ifstream;

const int MAX_LENGTH = 1000;
const int MAX_HEIGHT = 1000;

#pragma once

struct FileHeader
{
    char fileType[2];
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;
};

struct InfoHeader
{
    unsigned long biSize;
    unsigned long biWidth;
    unsigned long biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long biCompression;
    unsigned long biSizeImage;
    unsigned long biXPixelsPerMeter;
    unsigned long biYPixelsPerMeter;
    unsigned long biClrUsed;
    unsigned long biClrImportant;
    
    unsigned long PixelCount;    //# of pixles in file
};

class Picture
{
private:
    FileHeader fileHeader;
    InfoHeader infoHeader;
    RGBTriple* pixels;
    
    void InitializeFileHeader(int height, int width);
    void InitializeInfoHeader(int height, int width);
    void WriteFileHeader(std::ofstream& fout) const;
    void WriteInfoHeader(std::ofstream& fout) const;
    
    static Picture* pic;
    
    Picture(int width, int height, RGBTriple fillColor);
    Picture(const Picture& junk);
    ~Picture();
    void operator=(const Picture& junk);
public:
    static Picture& getInstance();
    void WriteToFile(const char* FileName) const;
    
    void SetPixelColor(int x, int y, RGBTriple color);
    void AddLine(int xStart, int yStart, int xEnd, int yEnd, RGBTriple color);
    void drawRectangle(int xStart, int yStart, int width, int height, RGBTriple color);
    void drawEquilateralTriangle(int xStart, int yStart, int length, RGBTriple color);
    void drawRightTriangle(int xStart, int yStart, int length, int height, RGBTriple color);

    
    int width();
    int height();
};

#endif /* Picture_hpp */
