//
//  Star.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Star.hpp"


Star::Star(coord start, double theLength, RGBTriple color):Shape(start, color)
{
    setFilled(false);
    int count = 0;
    if(start.x >= 0  && start.x <= MAX_LENGTH && start.y >= 0 && start.y <= MAX_HEIGHT)
    {
        setStartCoordinate(start);
        count++;
    }

    if(start.x + theLength <= MAX_LENGTH && start.x + theLength * sin(72 * PI / 180) <= 1000)
    {
        length = theLength;
        count++;
    }
    
    if(count == 2)
    {
        setFilled(true);
    }
}

void Star::draw()
{
    if(isFill())
    {
        Picture& p1 = Picture::getInstance();
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y + length * (sin(36 * PI / 180)), getStartCoordinate().x + length, getStartCoordinate().y + length * (sin(36 * PI / 180)), getColor());
        p1.AddLine(getStartCoordinate().x, getStartCoordinate().y + length * (sin(36 * PI / 180)), getStartCoordinate().x + length * (cos(36 * PI / 180)), getStartCoordinate().y, getColor());
        p1.AddLine(getStartCoordinate().x + 0.5 * length, getStartCoordinate().y + length * (sin(72 * PI / 180)), getStartCoordinate().x + length - length * (cos(36 * PI / 180)), getStartCoordinate().y, getColor());
        p1.AddLine(getStartCoordinate().x + 0.5 * length, getStartCoordinate().y + length * (sin(72 * PI / 180)),getStartCoordinate().x + length * (cos(36 * PI / 180)), getStartCoordinate().y, getColor());
        p1.AddLine(getStartCoordinate().x + length, getStartCoordinate().y + length * (sin(36 * PI / 180)), getStartCoordinate().x + length - length * (cos(36 * PI / 180)), getStartCoordinate().y, getColor());
    }
}
