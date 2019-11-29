//
//  Point.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include "Shape.hpp"
#include "Picture.hpp"
class Point : public Shape
{
public:
    Point(coord ,RGBTriple );
    void draw();
private:

};

#endif /* Point_hpp */
