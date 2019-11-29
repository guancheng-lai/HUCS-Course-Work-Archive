//
//  Line.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/16/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include "Shape.hpp"
#include "Picture.hpp"
class Line : public Shape
{
public:
    Line(coord ,coord ,RGBTriple );
    
    void draw();
private:
    coord endCoordinate;
};

class Line
{
public:
	Line();
	~Line();
};
#endif /* Line_hpp */
