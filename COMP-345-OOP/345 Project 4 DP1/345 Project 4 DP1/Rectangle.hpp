//
//  Rectangle.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include "Picture.hpp"
#include "Shape.hpp"
class Rectangle : public Shape
{
public:
    Rectangle(coord ,int ,int ,RGBTriple);
    void draw();
private:
    int length;
    int height;
};

class Rectangle
{
public:
	Rectangle();
	~Rectangle();
};






#endif /* Rectangle_hpp */
