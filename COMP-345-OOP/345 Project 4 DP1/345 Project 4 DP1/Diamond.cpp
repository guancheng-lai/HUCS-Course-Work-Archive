//
//  Diamond.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Diamond.hpp"

Diamond::Diamond(coord start, double theWidth, double theHeight, RGBTriple color):Shape(start, color)
{
    setFilled(false);
    int count = 0;
    if(start.x >= 0  && start.x <= MAX_LENGTH && start.y >= 0 && start.y <= MAX_HEIGHT)
    {
        setStartCoordinate(start);
        count++;
    }
    
    if(start.x + theWidth <= MAX_LENGTH && start.y + theHeight <= MAX_HEIGHT)
    {
        width = theWidth;
        height = theHeight;
        count++;
    }
    
    if(count == 2)
    {
        setFilled(true);
    }
}

void Diamond::draw()
{
    if(isFill())
    {
        Picture& p1 = Picture::getInstance();
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y + 0.5 * height, getStartCoordinate().x + 0.5 * width, getStartCoordinate().y, getColor());
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y + 0.5 * height, getStartCoordinate().x + 0.5 * width, getStartCoordinate().y + height, getColor());
        p1.AddLine(getStartCoordinate().x + width, getStartCoordinate().y + 0.5 * height, getStartCoordinate().x + 0.5 * width, getStartCoordinate().y, getColor());
        p1.AddLine(getStartCoordinate().x + width, getStartCoordinate().y + 0.5 * height, getStartCoordinate().x + 0.5 * width, getStartCoordinate().y + height, getColor());
    }
}


Diamond::Diamond()
{
}


Diamond::~Diamond()
{
}
