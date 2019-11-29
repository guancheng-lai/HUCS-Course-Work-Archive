//
//  Rectangle.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Rectangle.hpp"

Rectangle::Rectangle(coord start, int theLength, int theHeight, RGBTriple color): Shape(start, color)
{
    setFilled(false);
    int count = 0;
    if(start.x >= 0 && start.x <= MAX_LENGTH && start.y >= 0 && start.y <= MAX_HEIGHT)
    {
        setStartCoordinate(start);
        count++;
    }

    if(getStartCoordinate().x + theLength <= MAX_LENGTH)
    {
        length = theLength;
        count++;
    }
    
    if(getStartCoordinate().y + theHeight <= MAX_HEIGHT)
    {
        height = theHeight;
        count++;
    }
    
    if(count == 3)
    {
        setFilled(true);
    }
}

void Rectangle::draw()
{
    if(isFill())
    {
        Picture& p1 = Picture::getInstance();
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y, getStartCoordinate().x + length, getStartCoordinate().y, getColor());
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y, getStartCoordinate().x, getStartCoordinate().y + height, getColor());
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y + height, getStartCoordinate().x + length, getStartCoordinate().y + height, getColor());
        p1.AddLine(getStartCoordinate().x + length, getStartCoordinate().y, getStartCoordinate().x + length, getStartCoordinate().y + height, getColor());
    }
}


Rectangle::Rectangle()
{
}


Rectangle::~Rectangle()
{
}
