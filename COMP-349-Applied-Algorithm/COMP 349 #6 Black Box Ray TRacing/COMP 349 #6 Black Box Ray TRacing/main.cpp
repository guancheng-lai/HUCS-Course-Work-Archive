//
//  main.cpp
//  COMP 349 #6 Black Box Ray TRacing
//
//  Created by Guancheng Lai on 10/2/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QString>

const int LENGTH = 10;

enum Direction
{
    up,
    down,
    left,
    right
};

enum RayStatus
{
    hit,
    getOut,
    reflection,
    onGoing
};

struct Coordinate
{
    int row;
    int col;
    Direction direction;
};

void output(std::ofstream &fout, Coordinate current, Coordinate startPoint, RayStatus rayStatus, bool &firstOutput)
{
    if (!firstOutput)
    {
        fout << std::endl;
    }
    firstOutput = false;
    
    if (current.row == startPoint.row && current.col == startPoint.col && rayStatus == reflection)
    {
        fout << "R" ;
        std::cout << "R" << std::endl;
    }
    else if (rayStatus == hit)
    {
        fout << "H" ;
        std::cout << "H" << std::endl;
    }
    else if (current.row == startPoint.row && current.col == startPoint.col)
    {
        fout << "R" ;
        std::cout << "R" << std::endl;
    }
    else
    {
        if (current.row == 0)
        {
            fout << "T" << current.col ;
            std::cout << "T" << current.col << std::endl;
        }
        else if (current.row == LENGTH - 1)
        {
            fout << "B" << current.col ;
            std::cout << "B" << current.col << std::endl;
        }
        else if (current.col == 0)
        {
            fout << "L" << current.row ;
            std::cout << "L" << current.row << std::endl;
        }
        else if (current.col == LENGTH - 1)
        {
            fout << "R" << current.row ;
            std::cout << "R" << current.row << std::endl;
        }
    }
}

void getNewDirection(Coordinate &cur, char gameboard[LENGTH][LENGTH])
{
    bool left_top = gameboard[cur.row - 1][cur.col - 1] == '@' ? true : false ;
    bool left_bottom = gameboard[cur.row + 1][cur.col - 1] == '@' ? true : false ;
    bool right_top = gameboard[cur.row - 1][cur.col + 1] == '@' ? true : false ;
    bool right_bottom = gameboard[cur.row + 1][cur.col + 1] == '@' ? true : false ;
    
    if (cur.direction == down)
    {
        if (left_bottom && right_bottom)
        {
            cur.direction = up;
        }
        else if (left_bottom)
        {
            cur.direction = right;
        }
        else if (right_bottom)
        {
            cur.direction = left;
        }
    }
    else if (cur.direction == up)
    {
        if (left_top && right_top)
        {
            cur.direction = down;
        }
        else if (left_top)
        {
            cur.direction = right;
        }
        else if (right_top)
        {
            cur.direction = left;
        }
    }
    else if (cur.direction == left)
    {
        if (left_top && left_bottom)
        {
            cur.direction = right;
        }
        else if (left_top)
        {
            cur.direction = down;
        }
        else if (left_bottom)
        {
            cur.direction = up;
        }
    }
    else if (cur.direction == right)
    {
        if (right_top && right_bottom)
        {
            cur.direction = left;
        }
        else if (right_top)
        {
            cur.direction = down;
        }
        else if (right_bottom)
        {
            cur.direction = up;
        }
    }
    
    
}

bool isBorder(Coordinate cur)
{
    if (cur.row == 0 || cur.row == LENGTH - 1 || cur.col == 0 || cur.col == LENGTH - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isReflection(Coordinate cur, char gameboard[LENGTH][LENGTH])
{
    bool left_top = gameboard[cur.row - 1][cur.col - 1] == '@' ? true : false ;
    bool left_bottom = gameboard[cur.row + 1][cur.col - 1] == '@' ? true : false ;
    bool right_top = gameboard[cur.row - 1][cur.col + 1] == '@' ? true : false ;
    bool right_bottom = gameboard[cur.row + 1][cur.col + 1] == '@' ? true : false ;
    
    if (left_top || left_bottom || right_top || right_bottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isAtom (Coordinate cur, char gameboard[LENGTH][LENGTH])
{
    Coordinate next = cur;
    
    if (cur.direction == up)
    {
        next.row--;
    }
    else if (cur.direction == down)
    {
        next.row++;
    }
    else if (cur.direction == left)
    {
        next.col--;
    }
    else
    {
        next.col++;
    }
    
    
    if (gameboard[next.row][next.col] == '@')
    {
        return true;
    }
    else
    {
        return false;
    }
}

RayStatus checkNextStep(Coordinate &cur, char gameboard[LENGTH][LENGTH], RayStatus &rayStatus, bool &firstTime)
{
    if (isAtom(cur, gameboard))
    {
        rayStatus = hit;
    }
    else if (isReflection(cur, gameboard))
    {
        if (firstTime)
        {
            rayStatus = reflection;
        }
        else
        {
            getNewDirection(cur, gameboard);
        }
    }
    else if (isBorder(cur) && !firstTime)
    {
        rayStatus = getOut;
    }
    else
    {
        getNewDirection(cur, gameboard);
    }
    
    return rayStatus;
}

Coordinate makingMove(Coordinate cur)
{
    Coordinate result = cur;
    
    if (cur.direction == down)
    {
        result.row++;
    }
    else if (cur.direction == up)
    {
         result.row--;
    }
    else if (cur.direction == left)
    {
         result.col--;
    }
    else if (cur.direction == right)
    {
         result.col++;
    }
    
    return result;
}



Coordinate determineRayStartPoint(std::string rayInfo)
{
    Coordinate result;
    
    if (rayInfo[0] == 'T')
    {
        result.row = 0;
        result.col = int(rayInfo[1]) - 48;
        result.direction = down;
    }
    else if (rayInfo[0] == 'B')
    {
        result.row = LENGTH - 1;
        result.col = int(rayInfo[1]) - 48;
        result.direction = up;
    }
    else if (rayInfo[0] == 'L')
    {
        result.col = 0;
        result.row = int(rayInfo[1]) - 48;
        result.direction = right;
    }
    else
    {
        result.col = LENGTH - 1;
        result.row = int(rayInfo[1]) - 48;
        result.direction = left;
    }
    
    return result;
}

void initializeGameboard(std::ifstream &fin, char gameboard[LENGTH][LENGTH], char fisrt)
{
    for (int i = 1; i < LENGTH - 1; i++)
    {
        for (int j = 1; j < LENGTH - 1; j++)
        {
            if (i == 1 && j == 1)
            {
                gameboard[i][j] = fisrt;
            }
            else
            {
                fin >> gameboard[i][j];
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("blackbox.in");
    std::ofstream fout("blackbox.out");
    
    if (fin.good())
    {
        char ch;
        fin >> ch;
        
        bool firstOutput(true);
        
        while (fin && ch != 'X')
        {
            char gameboard[LENGTH][LENGTH];
            initializeGameboard(fin, gameboard, ch);
            
            int numOfRay;
            fin >> numOfRay;
            fin.ignore();
            
            for (int i = 0; i < numOfRay; i++)
            {
                std::string ray;
                getline(fin, ray);
                Coordinate startPoint = determineRayStartPoint(ray);
                Coordinate current = startPoint;
                RayStatus rayStatus = onGoing;
                bool firstTime(true);
                
                rayStatus = checkNextStep(current, gameboard, rayStatus, firstTime);
                
                while (rayStatus == onGoing)
                {
                    firstTime = false;
                    current = makingMove(current);
                    rayStatus = checkNextStep(current, gameboard, rayStatus, firstTime);
                    
                }
                
                output(fout, current, startPoint, rayStatus, firstOutput);
            }
            
        
            fin >> ch;
        }
    }
}
