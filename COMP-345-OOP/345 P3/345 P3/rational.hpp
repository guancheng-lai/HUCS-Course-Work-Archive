//
//  rational.hpp
//  345 P3
//
//  Created by Guancheng Lai on 1/29/18.
//  Copyright � 2018 Guancheng Lai. All rights reserved.
//

#ifndef rational_h
#define rational_h
#include <iostream>
#include <string>

class rational
{
public:
    rational(long numerator = 0, long denominator = 1);
    ~rational();
    long getNumerator() const;
    long getDenominator() const;
    
    //Binary operators
    rational& operator= (const rational &);
    
    //Unary operators
    const rational& operator++();
    rational operator++(int);
    const rational& operator--();
    rational operator--(int);
    rational& operator+=(const rational &);
    rational& operator-=(const rational &);
    rational& operator*=(const rational &);
    rational& operator/=(const rational &);
    
    //Convert functions
    explicit operator double() const;
    std::string operator()() const;
    
    void reduce();
private:
    long numerator;
    long denominator;
};

long LeastCommonMultiple(long, long);
long GreatestCommonDivisor(long, long);

std::ostream& operator<<(std::ostream &, const rational &);
std::istream& operator>>(std::istream &, rational &);

//Non-member binary operators overloading prototype
rational operator+ (const rational &, const rational &);
rational operator- (const rational &, const rational &);
rational operator* (const rational &, const rational &);
rational operator/ (const rational &, const rational &);
rational operator^ (const rational &, int);

bool operator== (const rational &, const rational &);
bool operator!= (const rational &, const rational &);
bool operator> (const rational &, const rational &);
bool operator< (const rational &, const rational &);
bool operator>= (const rational &, const rational &);
bool operator<= (const rational &, const rational &);




















#endif /* rational_hpp */

