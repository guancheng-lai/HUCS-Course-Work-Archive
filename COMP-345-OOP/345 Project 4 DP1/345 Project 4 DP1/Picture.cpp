//
//  Picture.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/9/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Picture.hpp"

Picture* Picture::pic = NULL;

Picture &Picture::getInstance()
{
    RGBTriple rgb1(255, 255, 255);
    if(pic == NULL)
    {
        pic = new Picture(MAX_LENGTH, MAX_HEIGHT, rgb1);
    }
    return *pic;
}

Picture::Picture(const Picture& junk){}

Picture::Picture(int width, int height, RGBTriple fillColor)
{
    InitializeFileHeader(width, height);
    InitializeInfoHeader(width, height);
    
    pixels = new RGBTriple[infoHeader.PixelCount];
    
    int i = 0;
    for(unsigned int row = 0; row < infoHeader.biHeight; row++)
    {
        for(unsigned int column = 0; column < infoHeader.biWidth; column++, i ++)
        {
            pixels[i] = fillColor;
        }
        
    }
}



void Picture::SetPixelColor(int x, int y, RGBTriple color)
{
    if(x < infoHeader.biWidth && y < infoHeader.biHeight)
    {
        int index = y * infoHeader.biWidth + x;
        pixels[index] = color;
    }
}

void Picture::AddLine(int xStart, int yStart, int xEnd, int yEnd, RGBTriple color)
{
    //y = mx + b
    //y - y0 = m( x - x0 )
    //m=(y-y0)/(x-x0)
    //x = (y-b)/m;
    if (xStart!=xEnd)
    {
        double m = ((double)yStart-(double)yEnd)/((double)xStart-(double)xEnd);
        double b = yStart - (m * xStart);
        if(abs(yStart-yEnd) < abs(xStart-xEnd))
        {
            int x1 = (xStart<xEnd)?xStart:xEnd;
            int x2 = (xStart<xEnd)?xEnd:xStart;
            //change in x is greater than change in y
            for(int x = x1; x<=x2;x++)
            {
                int y = floor((m*x) + b);
                SetPixelColor(x,y,color);
            }
        }
        else
        {
            //change in y is greater than change in x
            int y1 = (yStart<yEnd)?yStart:yEnd;
            int y2 = (yStart<yEnd)?yEnd:yStart;
            //change in x is greater than change in y
            for(int y = y1; y<=y2;y++)
            {
                int x = floor((y-b) / m);
                SetPixelColor(x,y,color);
            }
        }
    }
    else
    {
        int y1 = (yStart<yEnd)?yStart:yEnd;
        int y2 = (yStart<yEnd)?yEnd:yStart;
        int x = xStart;
        for(int y = y1; y<=y2;y++)
        {
            SetPixelColor(x,y,color);
        }
    }
}

void Picture::InitializeFileHeader(int width, int height)
{
    int paddedSize = height * ( width/8 + (4- (width/8%4)));
    
    fileHeader.fileType[0] = 'B';
    fileHeader.fileType[1] = 'M';
    fileHeader.bfSize = paddedSize + 54;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = 54;
}

void Picture::InitializeInfoHeader(int width, int height)
{
    infoHeader.biSize = 40;
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;
    infoHeader.biCompression = 0;
    infoHeader.biSizeImage = 0;
    infoHeader.biXPixelsPerMeter = 2834;
    infoHeader.biYPixelsPerMeter = 2834;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;
    
    infoHeader.PixelCount = infoHeader.biHeight * infoHeader.biWidth;
}



void Picture::WriteToFile(const char* FileName) const
{
    ofstream fout;
    fout.open(FileName, std::ios_base::binary); //destroys the old file
    
    WriteFileHeader(fout);
    WriteInfoHeader(fout);
    
    fout.seekp(fileHeader.bfOffBits); //should be 54
    int i = 0;
    for(unsigned int row = 0; row < infoHeader.biHeight; row++)
    {
        for(unsigned int column = 0; column < infoHeader.biWidth; column++, i ++)
        {
            fout.write((char*)&(pixels[i]), 3);
        }
        
        unsigned int b =  infoHeader.biWidth * 3;
        unsigned char junk = 0;
        
        while(b%4 != 0)
        {
            fout.write((char*)&junk, 1);
            b = b + 1;
        }
    }
    fout.close();
}

void Picture::WriteFileHeader(ofstream& fout)const
{
    fout.seekp(0);
    fout.write(fileHeader.fileType,2);
    fout.write((char*)&fileHeader.bfSize,4);
    fout.write((char*)&fileHeader.bfReserved1,2);
    fout.write((char*)&fileHeader.bfReserved2,2);
    fout.write((char*)&fileHeader.bfOffBits,4);
}

void Picture::WriteInfoHeader(ofstream& fout) const
{
    fout.seekp(14);
    fout.write((char*)&infoHeader.biSize,4);
    fout.write((char*)&infoHeader.biWidth,4);
    fout.write((char*)&infoHeader.biHeight,4);
    fout.write((char*)&infoHeader.biPlanes,2);
    fout.write((char*)&infoHeader.biBitCount,2);
    fout.write((char*)&infoHeader.biCompression,4);
    fout.write((char*)&infoHeader.biSizeImage,4);
    fout.write((char*)&infoHeader.biXPixelsPerMeter,4);
    fout.write((char*)&infoHeader.biYPixelsPerMeter,4);
    fout.write((char*)&infoHeader.biClrUsed,4);
    fout.write((char*)&infoHeader.biClrImportant,4);
}

int Picture::width()
{
    return infoHeader.biWidth;
}

int Picture::height()
{
    return infoHeader.biHeight;
}

void Picture::operator=(const Picture& junk){}

Picture::~Picture()
{
    if(pixels != NULL)
    {
        delete pixels;
    }
}
