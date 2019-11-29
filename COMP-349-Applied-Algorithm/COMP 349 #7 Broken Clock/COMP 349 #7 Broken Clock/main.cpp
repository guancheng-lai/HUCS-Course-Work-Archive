//
//  main.cpp
//  COMP 349 #7 Broken Clock
//
//  Created by Guancheng Lai on 9/17/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;

const std::bitset<8> zero   ("11101111");
const std::bitset<8> one    ("01001001");
const std::bitset<8> two    ("10111011");
const std::bitset<8> three  ("11011011");
const std::bitset<8> four   ("01011101");
const std::bitset<8> five   ("11010111");
const std::bitset<8> six    ("11110111");
const std::bitset<8> seven  ("01001011");
const std::bitset<8> eight  ("11111111");
const std::bitset<8> nine   ("01011111");

const std::bitset<8> getCorrespondingBitset(int i)
{
    switch (i)
    {
        case 0:
            return zero;

        case 1:
            return one;

        case 2:
            return two;

        case 3:
            return three;

        case 4:
            return four;

        case 5:
            return five;

        case 6:
            return six;

        case 7:
            return seven;
            
        case 8:
            return eight;
            
        case 9:
            return nine;
            
        default:
            return NULL;
    }
}

void outputConfusedNumber(std::ofstream &fout, const std::vector< std::pair<int, int> > &brokenPair)
{
    if (brokenPair.empty())
    {
        return ;
    }
    
    int current(brokenPair[0].first);
    fout << " {" << current ;
    for (size_t i = 0; i < brokenPair.size(); i++)
    {
        if (brokenPair[i].first == current)
        {
            fout  << "," << brokenPair[i].second;
        }
        else
        {
            current = brokenPair[i].first;
            fout << "} {" << current << "," << brokenPair[i].second ;
        }
        
        
    }
    fout << "}";
}

void outputBrokenLEDs(std::ofstream &fout, const std::vector<int> &ledList)
{
    fout << "Case <";
    for (int i = 0; i < ledList.size(); i++)
    {
        if (i != 0)
        {
            fout << ",";
        }
        
        fout << ledList[i] ;
    }
    fout << ">:";
}

bool ifAlreadyFound(const std::vector< std::pair<int, int> > &vectorOfPair, int target)
{
    bool result = false;
    
    size_t sz = vectorOfPair.size();
    for (int i = 0; i < sz; i++)
    {
        if (vectorOfPair[i].second == target)
        {
            result = true;
            break;
        }
    }
    
    return result;
}

void lookingForConfuseClock(std::vector< std::pair<int, int> > &brokenPair, const std::bitset<8> &workingLed)
{
    int count(0);
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10 && !ifAlreadyFound(brokenPair, i); j++)
        {
            if ((getCorrespondingBitset(i) & workingLed) == (getCorrespondingBitset(j) & workingLed))
            {
                count++;
                brokenPair.push_back(std::pair<int, int> (i, j));
                cout << i << " - " << j << " ---- " << (getCorrespondingBitset(i) & workingLed) << endl;
            }
        }
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("led.in");
    std::ofstream fout("led.out");
    
    if (fin.good())
    {
        bool firstTime(true);
        while (fin.is_open())
        {
            std::vector<int> ledList;
            int inValue;
            fin >> inValue;
            
            while (fin && inValue != 0)
            {
                ledList.push_back(inValue);
                fin >> inValue;
            }
    
            if (inValue == 0 && ledList.empty())
            {
                break;
            }
            else if (!firstTime)
            {
                fout << endl;
            }
            firstTime = false;
            
            
            // Begin here
            std::bitset<8> workingLed("11111111");
            for (auto i : ledList)
            {
                workingLed[i] = 0;
            }
            
            std::vector< std::pair<int, int> > brokenPair;
            lookingForConfuseClock(brokenPair, workingLed);
            outputBrokenLEDs(fout, ledList);
            outputConfusedNumber(fout, brokenPair);
        }
    }
}
