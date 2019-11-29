//
//  main.cpp
//  345 P3
//
//  Created by Guancheng Lai on 1/29/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//


#include "rational.hpp"
using std::cout;
using std::cin;
using std::endl;

int main(int argc, const char * argv[]) {
    rational r1(1,2);
    rational r2(1,4);
    r2+=r1;
    cout << r2;
    r1*=r2;
    cout << r1;
    return 0;
}
