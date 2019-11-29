//
//  Star.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Star_hpp
#define Star_hpp

#include <stdio.h>
#include <math.h>
#include "Shape.hpp"
#include "Picture.hpp"

#define PI 3.14159265

class Star : public Shape
{
public:
    Star(coord, double, RGBTriple);
    
    void draw();
private:
    double length;
};
#endif /* Star_hpp */
