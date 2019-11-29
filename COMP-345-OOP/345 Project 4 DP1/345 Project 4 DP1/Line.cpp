//
//  Line.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Line.hpp"
Line::Line(coord start, coord end, RGBTriple color) : Shape(start, color)
{
    setFilled(false);
    int count = 0;
    if(start.x >= 0 && start.x <= MAX_LENGTH && start.y >= 0 && start.y <= MAX_HEIGHT)
    {
        setStartCoordinate(start);
        count++;
    }
    
    if(end.x >= 0 && end.x <= MAX_LENGTH && end.y >= 0 && end.y <= MAX_HEIGHT)
    {
        endCoordinate = end;
        count++;
    }
    
    if(count == 2)
    {
        setFilled(true);
    }
};


void Line::draw()
{
    if(isFill())
    {
        Picture& p1 = Picture::getInstance();
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y, endCoordinate.x, endCoordinate.y, getColor());
    }
}


Line::Line()
{
}


Line::~Line()
{
}
