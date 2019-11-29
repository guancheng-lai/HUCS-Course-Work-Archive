//
//  main.cpp
//  COMP 349 Problem #2 Robot Motion
//
//  Created by Guancheng Lai on 8/23/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;

struct coordinate
{
    int x;
    int y;
};

void printGrid(std::vector<std::vector<std::string>> grid, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

bool checkEndOfFile(int a, int b, int c, int d)
{
    int count = 0;
    if (a == 0) {
        count++;
    }
    
    if (b == 0) {
        count++;
    }

    if (c == 0) {
        count++;
    }
    
    if (d == 0) {
        count++;
    }
    
    if (count >= 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

coordinate getMove(std::string c, coordinate cur)
{
    coordinate result(cur);
    
    if (c == "N")
    {
        result.y = cur.y - 1;
        result.x = cur.x;
    }
    else if (c == "S")
    {
        result.y = cur.y + 1;
        result.x = cur.x;
    }
    else if (c == "E")
    {
        result.y = cur.y;
        result.x = cur.x + 1;
    }
    else if (c == "W")
    {
        result.y = cur.y;
        result.x = cur.x - 1;
    }
    
    return result;
}

bool checkIfExit(int row, int column, coordinate current)
{
    if (current.x > column - 1 || current.x < 0 || current.y > row - 1 || current.y < 0)
    {
        return true;
    }
    
    return false;
}

void freeMemory(std::vector<std::vector<std::string> > &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[1].size(); j++)
        {
            grid[i][j] = nullptr;
        }
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("robot.in");
    std::ofstream fout("robot.out");
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            int row, column, startX, startY;
            fin >> row >> column >> startY >> startX;
            fin.ignore();
            
            if (!checkEndOfFile(row, column, startX, startY))
            {
                std::vector<std::vector<std::string> > grid(row);
                for (int i = 0; i < row; i++)
                {
                    std::vector<std::string> rows(column);
                    grid[i] = rows;
                }
                
                
                for (int i = 0; i < row; i ++)
                {
                    std::string line;
                    std::getline(fin, line);
                    
                    for (int j = 0; j < column; j++)
                    {
                        char c = line[j];
                        grid[i][j] = c;
                    }
                }
            
                int count = 0;
                
                coordinate current;
                current.x = startX - 1;
                current.y = startY - 1;
                
                std::string move = grid[current.y][current.x];
                std::string num = std::to_string(count);
                grid[current.y][current.x] = std::to_string(count);
                
                bool solved = false;
                while (1)
                {
                    coordinate next = getMove(move, current);
                    
                    // Loop
                    if (isdigit(move[0]))
                    {
                        int loopCount = atoi(move.c_str());
                        
                        fout << loopCount;
                        
                        if (loopCount == 1)
                        {
                            fout << " instruction before a loop of " << count - loopCount;
                        }
                        else
                        {
                            fout << " instructions before a loop of " << count - loopCount;
                        }
                        
                        if (count - loopCount == 1)
                        {
                            fout << " instruction" << endl;
                        }
                        else
                        {
                            fout << " instructions" << endl;
                        }
                        
                        
                        // cout << loopCount << " instructions before a loop of " << count - loopCount << " instructions" << endl;
                        break;
                    }
                    
                    //  Exit
                    if (checkIfExit(row, column, next))
                    {
                        // cout << count + 1 << " instructions before exit" << endl;
                        
                        if (count == 0)
                        {
                            fout << count + 1 << " instruction before exit" << endl;
                        }
                        else
                        {
                            fout << count + 1 << " instructions before exit" << endl;
                        }
                        
                        
                        
                        std::string a = std::to_string(count);
                        grid[current.y][current.x] = a;
                        break;
                    }
                    
                    grid[current.y][current.x] = std::to_string(count);
                    count++;
                    current = next;
                    move = grid[next.y][next.x];
                }
                
                if (solved)
                {
                    freeMemory(grid);
                }
            }
            else
            {
                break;
            }
            
        }
    }
    
    fin.close();
    fout.close();
}























