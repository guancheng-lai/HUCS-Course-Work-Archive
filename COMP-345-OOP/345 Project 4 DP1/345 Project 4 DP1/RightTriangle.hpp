//
//  RightTriangle.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef RightTriangle_hpp
#define RightTriangle_hpp

#include <stdio.h>
#include "Shape.hpp"
#include "Picture.hpp"
class RightTriangle : public Shape
{
public:
    RightTriangle(coord , int ,int ,RGBTriple);
    void draw();
private:
    int length;
    int height;
};

class RGBTriple
{
public:
	RGBTriple();
	~RGBTriple();
};
#endif /* RightTriangle_hpp */
