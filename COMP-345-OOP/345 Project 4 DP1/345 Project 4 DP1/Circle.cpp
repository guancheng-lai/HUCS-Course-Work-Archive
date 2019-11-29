//
//  Circle.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/17/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Circle.hpp"
Circle::Circle(coord start, double theRadius, RGBTriple color):Shape(start, color)
{
    setFilled(false);
    if(start.x + theRadius <= MAX_LENGTH && start.x - theRadius >= 0 && start.y + theRadius <= MAX_HEIGHT && start.y - theRadius >= 0)
    {
        setStartCoordinate(start);
        radius = theRadius;
        tol = radius;
        setFilled(true);
    }
}

void Circle::draw()
{
    if(isFill())
    {
        Picture& p1 = Picture::getInstance();
        for(int j = 0; j < MAX_LENGTH; j++)
        {
            for(int k = 0; k < MAX_HEIGHT; k++)
            {
                if(abs(pow(abs(getStartCoordinate().x - j),2) + pow(abs(getStartCoordinate().y - k),2) - pow(radius,2)) < tol)
                {
                    p1.SetPixelColor(j, k, getColor());
                }
            }
        }
    }
}


Circle::Circle()
{
}


Circle::~Circle()
{
}
