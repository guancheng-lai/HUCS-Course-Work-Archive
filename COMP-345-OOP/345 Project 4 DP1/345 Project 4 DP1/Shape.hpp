//
//  Shape.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>
#include "Picture.hpp"
#include "Coordinate.hpp"
class Shape
{
public:
    Shape(coord, RGBTriple);
    ~Shape();
    
    void setColor(RGBTriple );
    RGBTriple getColor();
    void setStartCoordinate(coord );
    coord getStartCoordinate();
    void setFilled(bool );
    bool isFill();
    
    
    virtual void draw() = 0;
private:
    RGBTriple color;
    coord startCoordinate;
    bool isFilled;
};
#endif /* Shape_hpp */
