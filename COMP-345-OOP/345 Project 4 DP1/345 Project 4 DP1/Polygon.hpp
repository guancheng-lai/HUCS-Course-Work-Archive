//
//  Polygon.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include <stdio.h>
#include "Shape.hpp"
#include "Picture.hpp"
class Polygon : public Shape
{
public:
    Polygon(coord, coord, RGBTriple);
    void draw();
private:
    coord endCoordinate;
};

class Polygon
{
public:
	Polygon();
	~Polygon();
};
#endif /* Polygon_hpp */
