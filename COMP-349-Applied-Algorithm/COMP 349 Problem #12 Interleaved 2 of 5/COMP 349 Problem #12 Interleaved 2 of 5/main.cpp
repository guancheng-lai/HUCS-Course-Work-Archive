//
//  main.cpp
//  COMP 349 Problem #12 Interleaved 2 of 5
//
//  Created by Guancheng Lai on 9/22/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

const std::string zero = "nnwwn";
const std::string one = "wnnnw";
const std::string two = "nwnnw";
const std::string three = "wwnnn";
const std::string four = "nnwnw";
const std::string five = "wnwnn";
const std::string six = "nwwnn";
const std::string seven = "nnnww";
const std::string eight = "wnnwn";
const std::string nine = "nwnwn";

const std::string getCorrectsponding(const char c)
{
    std::string result;
    
    switch (c)
    {
        case '0':
            result = zero;
            break;
            
        case '1':
            result = one;
            break;
            
        case '2':
            result = two;
            break;
            
        case '3':
            result = three;
            break;
            
        case '4':
            result = four;
            break;
            
        case '5':
            result = five;
            break;
            
        case '6':
            result = six;
            break;
            
        case '7':
            result = seven;
            break;
            
        case '8':
            result = eight;
            break;
            
        case '9':
            result = nine;
            break;
            
        default:
            break;
    }
    
    return result;
}

void processingNumbersToBarcode(const std::string &line, std::string &result)
{
    result += "NnNn";
    
    std::string bar;
    std::string space;
    for (int i = 0; i < line.size(); i += 2)
    {
        bar = getCorrectsponding(line[i]);
        space = getCorrectsponding(line[i+1]);
        
        for (int j = 0; j < 5; j++)
        {
            result += toupper(bar[j]);
            result += space[j];
        }
    }
    
    result += "WnN";
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("barcode.in");
    std::ofstream fout("barcode.out");
    
    if (fin.good())
    {
        std::string line;
        getline(fin, line);
        
        bool firstTime(true);
        
        while (line != "0")
        {
            if (firstTime)
            {
                firstTime = false;
            }
            else
            {
                fout << endl;
            }
            
            std::string result;
            
            if (line.size() % 2 != 0)
            {
                line = "0" + line;
            }
            
            processingNumbersToBarcode(line, result);
            
            fout << result;
            cout << result << endl;
            
            getline(fin, line);
        }
    }
    
}
