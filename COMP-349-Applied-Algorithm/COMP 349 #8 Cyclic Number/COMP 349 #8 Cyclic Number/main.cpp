//
//  main.cpp
//  COMP 349 #8 Cyclic Number
//
//  Created by Guancheng Lai on 9/3/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void creatingVector (std::vector<int> &myInts, std::string line)
{
    size_t length = line.size();
    const char * c = line.c_str();
    
    for (int i = length - 1; i >= 0; i--)
    {
        myInts.push_back(int(c[i]) - 48);
    }
}

void multiply(const std::vector<int> &number, std::vector<int>& afterMultiply, int times)
{
    int addToNext(0);
    afterMultiply.resize(number.size());
    for (int i = 0; i < number.size(); i++)
    {
        int result = number[i] * times + addToNext;
        
        if (result > 9)
        {
            addToNext = (result / 10);
        }
        else
        {
            addToNext = 0;
        }
        
        afterMultiply[i] = (result % 10);
    }
}

bool isCyclic(std::vector<int> &a, std::vector<int> &b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    
    for (int i = 0; i < b.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    
    return true;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("cyclic.in");
    std::ofstream fout("cyclic.out");
    
    if (fin.good())
    {
        std::string line;
        getline(fin, line);
        
        while (fin)
        {
            int digits = int(line.size());
            std::vector<int> myNumber;
            creatingVector(myNumber, line);

            int count(0);
            for (int i = 1; i <= digits; i++)
            {
                std::vector<int> afterMultiply;
                multiply(myNumber, afterMultiply, i);
                
                std::vector<int> beforeMultiply(myNumber);
                size_t numOfZerosToAdd = afterMultiply.size() - myNumber.size();
                for (int j = 0; j < numOfZerosToAdd; j++) { beforeMultiply.push_back(0); }
                
                if (isCyclic(beforeMultiply, afterMultiply))
                {
                    count++;
                }
            }
            
            if (count == digits)
            {
                // cout << line << " is cyclic" << std::endl;
                fout << line << " is cyclic";
            }
            else
            {
                // cout << line << " is not cyclic" << std::endl;
                fout << line << " is not cyclic";
            }
            
            
            getline(fin, line);
            
            if (line == "00")
            {
                break;
            }
            else
            {
                fout << endl;
            }
        }
    }
    
}
