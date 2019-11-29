//
//  RGBTriple.hpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/9/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef RGBTriple_hpp
#define RGBTriple_hpp

#include <stdio.h>
//#pragma once;

struct RGBTriple
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    
    RGBTriple();
    RGBTriple(unsigned char blue, unsigned char green, unsigned char red);
};
#endif /* RGBTriple_hpp */
