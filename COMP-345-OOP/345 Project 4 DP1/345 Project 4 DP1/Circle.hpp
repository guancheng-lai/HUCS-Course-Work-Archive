//
//  Circle.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/17/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include "Shape.hpp"
#include "Picture.hpp"
class Circle : public Shape
{
public:
    Circle(coord, double, RGBTriple);
    void draw();
private:
    double radius;
    double tol;
};

class Circle
{
public:
	Circle();
	~Circle();
};
#endif /* Circle_hpp */
