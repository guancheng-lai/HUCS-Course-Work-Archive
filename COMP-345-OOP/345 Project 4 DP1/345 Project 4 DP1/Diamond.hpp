//
//  Diamond.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Diamond_hpp
#define Diamond_hpp

#include <stdio.h>
#include "Shape.hpp"
#include "Picture.hpp"
class Diamond : public Shape
{
public:
    Diamond(coord, double ,double ,RGBTriple);
    void draw();
private:
    double width;
    double height;
};

class Diamond
{
public:
	Diamond();
	~Diamond();
};
#endif /* Diamond_hpp */
