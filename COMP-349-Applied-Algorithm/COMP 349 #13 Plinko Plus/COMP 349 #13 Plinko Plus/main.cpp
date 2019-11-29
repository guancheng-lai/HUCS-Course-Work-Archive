//
//  main.cpp
//  COMP 349 #13 Plinko Plus
//
//  Created by Guancheng Lai on 9/24/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

enum Direction {L, R};

struct Node
{
    int value;
    int biggestSum;
    Direction direction;
};

void dynamicProgramming(int i, int j, std::vector<Node*> &matrix)
{
    if (i != 0)
    {
        if (j == 0)
        {
            matrix[i][j].biggestSum = matrix[i][j].value + matrix[i - 1][0].biggestSum;
        }
        else if (j == i)
        {
            matrix[i][j].biggestSum = matrix[i][j].value + matrix[i - 1][j - 1].biggestSum;
        }
        else
        {
            matrix[i][j].biggestSum = (matrix[i - 1][j - 1].biggestSum >= matrix[i - 1][j].biggestSum ? matrix[i - 1][j - 1].biggestSum : matrix[i - 1][j].biggestSum) + matrix[i][j].value;
        }
    }
    else
    {
        matrix[i][j].biggestSum = matrix[i][j].value;
    }
}

int calculatingBiggest(int numOfLines, const std::vector<Node*> &matrix)
{
    int largestSum(0);
    
    for (int i = 0; i < numOfLines; i++)
    {
        if (matrix[numOfLines - 1][i].biggestSum > largestSum)
        {
            largestSum = matrix[numOfLines - 1][i].biggestSum;
        }
    }
    
    return largestSum;
}

void outputResult(std::ofstream &fout, bool firstTime, int largestSum)
{
    if (firstTime)
    {
        firstTime = false;
    }
    else
    {
        fout << endl;
    }
    fout << largestSum;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("plinko.in");
    std::ofstream fout("plinko.out");
    
    if (fin.good())
    {
        bool firstTime(true);
        int numOfLines(0);
        fin >> numOfLines;
        
        while (fin && numOfLines != 0)
        {
            std::vector<Node*> matrix(numOfLines);
            
            for (int i = 0; i < numOfLines; i++)
            {
                matrix[i] = new Node [i + 1];
                
                for (int j = 0; j < i + 1; j++)
                {
                    int num;
                    fin >> num;
                    matrix[i][j].value = num;
                    
                    dynamicProgramming(i, j, matrix);
                    
                    cout << matrix[i][j].value << "," << matrix[i][j].biggestSum << " ";
                }
                cout << endl;
            }
            
            int largestSum = calculatingBiggest(numOfLines, matrix);
            outputResult(fout, firstTime, largestSum);
            
            matrix.clear();
            fin >> numOfLines;
        }
        
    }
    
    
}

