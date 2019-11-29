//
//  Point.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Point.hpp"
Point::Point(coord start, RGBTriple color) : Shape(start, color)
{
    setFilled(false);
    if(start.x >= 0  && start.x <= MAX_LENGTH && start.y >= 0 && start.y <= MAX_HEIGHT)
    {
        setStartCoordinate(start);
        setFilled(true);
    }
}


void Point::draw()
{
    if(isFill())
    {
        Picture& p1 = Picture::getInstance();
        p1.SetPixelColor(getStartCoordinate().x, getStartCoordinate().y, getColor());
    }
}

