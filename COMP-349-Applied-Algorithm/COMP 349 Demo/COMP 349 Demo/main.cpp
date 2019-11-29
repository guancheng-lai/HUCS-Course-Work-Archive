//
//  main.cpp
//  COMP 349 Demo
//
//  Created by Guancheng Lai on 8/21/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>


unsigned long long factorial(unsigned long long n)
{
    if (n == 0)
    {
        return 0;
    }
    
    unsigned long long result(1);
    
    while (n != 0)
    {
        result *= n;
        n--;
    }
    
    return result;
}

unsigned long long exp(unsigned long long n, unsigned long long m)
{
    if (n == 0)
    {
        return 0;
    }
    
    unsigned long long result(1);
    
    for (int i = 0; i < m; i++)
    {
        result *= n;
    }
    
    return result;
}

unsigned long long combination(unsigned long long n, unsigned long long i)
{
    if (i == 0 || n == 0 || i == n)
    {
        return 1;
    }
    else
    {
        return combination(n - 1, i - 1) + combination(n - 1, i);
    }
}

unsigned long long function_S(unsigned long long m, unsigned long long n)
{
    unsigned long long result = 0;
    
    if (n == 1)
    {
        result = 1;
    }
    else if(m < n)
    {
        result = 0;
    }
    else if(m == n)
    {
        result = factorial(m);
    }
    else
    {
        unsigned long long combinationsResult(0);
        
        for (int i = 0; i < n; ++i)
        {
            combinationsResult += (combination(n, i) * function_S(m, i));
        }
        
        result = exp(n, m) - combinationsResult;
    }
    
    return result;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("surjections.in");
    std::ofstream fout("surjections.out");
    
    if (fin.is_open())
    {
        while(!fin.eof())
        {
            int n, m;
            
            fin >> n;
            fin >> m;
            
            if (n != 0 || m != 0)
            {
                unsigned long long result = function_S(n, m);
                fout << "S(";
                fout << n;
                fout << ",";
                fout << m;
                fout << ") = ";
                fout << result << std::endl;
            }
            

        }
    }
    
    fin.close();
    fout.close();
}




























