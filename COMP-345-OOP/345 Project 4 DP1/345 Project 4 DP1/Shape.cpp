//
//  Shape.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Shape.hpp"
Shape::Shape(coord start, RGBTriple color1)
{
    startCoordinate = start;
    color = color1;
}

void Shape::setFilled(bool filled)
{
    if(filled != 0)
    {
        isFilled = true;
    }
    else
    {
        isFilled = false;
    }
}

bool Shape::isFill()
{
    return isFilled;
}

void Shape::setColor(RGBTriple color1)
{
    color = color1;
}

RGBTriple Shape::getColor()
{
    return color;
}

void Shape::setStartCoordinate(coord start)
{
    startCoordinate = start;
}

coord Shape::getStartCoordinate()
{
    return startCoordinate;
}

Shape::~Shape(){}
