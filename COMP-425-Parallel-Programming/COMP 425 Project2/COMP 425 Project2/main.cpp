//
//  main.cpp
//  COMP 425 Project2
//
//  Created by Guancheng Lai on 10/10/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <limits>
#include <omp.h>

using std::cin;
using std::endl;
using std::cout;
using std::vector;

void printSheet(const vector< vector<int> > &timeSheet)
{
    size_t numOfPoints = timeSheet[0].size();
    
    for (int i = 0; i < numOfPoints; i++)
    {
        for (int j = 0; j < numOfPoints; j++)
        {
            cout << std::setw(7) << timeSheet[i][j];
        }
        cout << endl;
    }
    
    cout << endl;
}

int minOf (int a, int b)
{
    return a < b ? a : b;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("in.txt");
    
    int numOfLocations;
    fin >> numOfLocations;
    while (numOfLocations)
    {
        vector< vector<int> > timeSheet(numOfLocations, vector<int>(numOfLocations, 9999));
        
        for (int i = 0; i < numOfLocations; i++)
        {
            timeSheet[i][i] = 0;
        }
        
        int numOfPaths;
        fin >> numOfPaths;
        
        for (int i = 0; i < numOfPaths; i++)
        {
            int from, to, weight;
            fin >> from >> to >> weight;
            timeSheet[from][to] = weight;
        }
        
        printSheet(timeSheet);
        
        for (int k = 0; k < numOfLocations; k++)
        {
            for (int i = 0; i < numOfLocations; i++)
            {
                for (int j = 0; j < numOfLocations; j++)
                {
                    timeSheet[i][j] = minOf(timeSheet[i][j], timeSheet[i][k] + timeSheet[k][j]);
                }
            }
        }
        
        printSheet(timeSheet);
        
        cin >> numOfLocations;
    }
    
}
