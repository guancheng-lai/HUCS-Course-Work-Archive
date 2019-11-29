//
//  rational.cpp
//  345 P3
//
//  Created by Guancheng Lai on 1/29/18.
//  Copyright � 2018 Guancheng Lai. All rights reserved.
//

#include "rational.hpp"
#include <sstream>

rational::rational(long NewNumerator, long NewDenominator)
{
    if (NewDenominator == 0)
    {
        numerator = 0;
        denominator = 1;
    }
    else
    {
        numerator = NewNumerator;
        denominator = NewDenominator;
        reduce();
    }
}

rational::~rational() {}

long rational::getNumerator()const
{
    return numerator;
}

long rational::getDenominator()const
{
    return denominator;
}

void rational::reduce()
{
    long GCD = GreatestCommonDivisor(numerator, denominator);
    numerator = numerator / GCD;
    denominator = denominator / GCD;
}

long LeastCommonMultiple(long x, long y)
{
    long result = x;
    while (result % y != 0)
    {
        result += x;
    }
    return result;
}

long GreatestCommonDivisor(long x, long y)
{
    long remainder = x % y;
    while (remainder != 0)
    {
        x = y;
        y = remainder;
        remainder = x % y;
    }
    return y;
}

//Extraction and insertion overload

std::ostream& operator<<(std::ostream& output, const rational& rValue)
{
    if (rValue.getDenominator() == 1)
    {
        output << rValue.getNumerator() << std::endl;
    }
    else
    {
        if (rValue.getDenominator() < 0 && rValue.getNumerator() < 0)
        {
            output << abs(rValue.getNumerator()) << '/' << abs(rValue.getDenominator()) << std::endl;
        }
        else if (rValue.getDenominator() < 0 || rValue.getNumerator() < 0)
        {
            output << '-' << abs(rValue.getNumerator()) << '/' << abs(rValue.getDenominator()) << std::endl;
        }
        else
        {
            output << rValue.getNumerator() << '/' << rValue.getDenominator() << std::endl;
        }
        
    }
    return output;
}

std::istream& operator>>(std::istream& input, rational & rValue)
{
    long numerator, denominator;
    char junk;
    input >> numerator >> junk >> denominator;
    rValue = rational(numerator, denominator);
    return input;
}






//Binary operators
rational& rational::operator=(const rational & rValue)
{
    numerator = rValue.numerator;
    denominator = rValue.denominator;
    reduce();
    return *this;
}

rational operator+ (const rational& lValue, const rational& rValue)
{
    long lcmValue = LeastCommonMultiple(lValue.getDenominator(), rValue.getDenominator());
    rational result(lValue.getNumerator() * lcmValue / lValue.getDenominator() + rValue.getNumerator() * lcmValue / rValue.getDenominator(), lcmValue);
    result.reduce();
    return result;
}


rational operator- (const rational& lValue, const rational& rValue)
{
    long lcmValue = LeastCommonMultiple(lValue.getDenominator(), rValue.getDenominator());
    rational result(lValue.getNumerator() * lcmValue / lValue.getDenominator() -
                    rValue.getNumerator() * lcmValue / rValue.getDenominator()
                    , lcmValue);
    result.reduce();
    return result;
}


rational operator* (const rational& lValue, const rational& rValue)
{
    rational result(lValue.getNumerator() * rValue.getNumerator(),
                    lValue.getDenominator() * rValue.getDenominator());
    result.reduce();
    return result;
}

rational operator/ (const rational& lValue, const rational& rValue)
{
    rational result(lValue.getNumerator() * rValue.getDenominator(),
                    lValue.getDenominator() * rValue.getNumerator());
    result.reduce();
    return result;
}

rational operator^ (const rational& lValue, int times)
{
    rational result(lValue);
    while (times > 1)
    {
        result = result * lValue;
        times--;
    }
    result.reduce();
    return result;
}

bool operator> (const rational& lValue, const rational& rValue)
{
    bool result = false;
    if ((double)rValue < (double)lValue)
    {
        result = true;
    }
    return result;
}

bool operator< (const rational& lValue, const rational& rValue)
{
    bool result = false;
    if ((double)rValue > (double)lValue)
    {
        result = true;
    }
    return result;
}











//Unary operators

bool operator==(const rational & lValue, const rational & rValue)
{
    bool result = true;
    if (lValue.getNumerator() != rValue.getNumerator() || lValue.getDenominator() != rValue.getDenominator())
    {
        result = false;
    }
    return result;
}

bool operator!=(const rational & lValue, const rational & rValue)
{
    bool result = true;
    
    if (lValue.getNumerator() == rValue.getNumerator() && lValue.getDenominator() == rValue.getDenominator())
    {
        result = false;
    }
    return result;
}

bool operator<= (const rational & lValue, const rational & rValue)
{
    bool result = (lValue < rValue) || (lValue == rValue);
    return result;
}

bool operator>= (const rational & lValue, const rational & rValue)
{
    bool result = (lValue > rValue) || (lValue == rValue);
    return result;
}

const rational& rational::operator++()
{
    numerator += denominator;
    reduce();
    return *this;
}

rational rational::operator++(int Garbage)
{
    rational result = *this;
    numerator += denominator;
    reduce();
    return result;
}

const rational& rational::operator--()
{
    numerator = numerator - denominator;
    reduce();
    return *this;
}

rational rational::operator--(int Garbage)
{
    rational result = *this;
    numerator -= denominator;
    reduce();
    return result;
}

rational& rational::operator+=(const rational &rValue)
{
    long lcmValue = LeastCommonMultiple(this->getDenominator(), rValue.getDenominator());
    numerator = this->getNumerator() * lcmValue / this->getDenominator() + rValue.getNumerator() * lcmValue / rValue.getDenominator();
    denominator = lcmValue;
    reduce();
    return *this;
}

rational& rational::operator-=(const rational &rValue)
{
    long lcmValue = LeastCommonMultiple(this->getDenominator(), rValue.getDenominator());
    numerator = this->getNumerator() * lcmValue / this->getDenominator() - rValue.getNumerator() * lcmValue / rValue.getDenominator();
    denominator = lcmValue;
    reduce();
    return *this;
}

rational& rational::operator*=(const rational &rValue)
{
    numerator = numerator * rValue.getNumerator();
    denominator = denominator * rValue.getDenominator();
    reduce();
    return *this;
}

rational& rational::operator/=(const rational &rValue)
{
    numerator = numerator * rValue.getDenominator();
    denominator = denominator * rValue.getNumerator();
    reduce();
    return *this;
}

std::string rational::operator()() const
{
    std::stringstream stream;
    stream << numerator << "/" << denominator;
    return stream.str();
}

rational::operator double() const
{
    return double(numerator) / double(denominator);
};





