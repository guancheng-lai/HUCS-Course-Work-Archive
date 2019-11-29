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
#include <iomanip>
#include <stack>

using std::cout;
using std::endl;

struct coordinate
{
    int x;
    int y;
    
    coordinate(int xCoord, int yCoord){this->x = xCoord; this->y = yCoord;}
    coordinate(){this->x = -1; this->y = -1;}
    coordinate(coordinate const &copy){this->x = copy.x;this->y = copy.y;}
};

struct node
{
    char character;
    coordinate coord;
    bool visited;
    
    node(){this->visited = false;this->character = ' ';}
    node(char c){this->character = c;}
    node(char c, coordinate coordinate){this->character = c;this->coord = coordinate;}
    node(char c, coordinate coordinate, bool isVisited){this->character = c;this->coord = coordinate;this->visited = isVisited;}
    node(node const &copy){this->character = copy.character; this->coord = copy.coord; this->visited = copy.visited;}
};

void copyGrid(const node copyFromGrid[4][4], node copyToGrid[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            copyToGrid[i][j].character = copyFromGrid[i][j].character;
            copyToGrid[i][j].coord = copyFromGrid[i][j].coord;
            copyToGrid[i][j].visited = copyFromGrid[i][j].visited;
        }
    }
}

void printGrid(const node grid[4][4])
{
    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j].visited)
            {
                cout << "*";
            }
            else
            {
                cout << grid[i][j].character;
            }
        }
        cout << endl;
    }
}

bool search(node grid[4][4], coordinate current, std::string word, int stringIndex)
{
    if (stringIndex == word.size())
    {
        return true;
    }
    
    std::stack<coordinate> stackOfCoordinate;
    
    //left side
    if (current.x > 0)
    {
        //left slot
        if (grid[current.y][current.x - 1].character == word[stringIndex] && !grid[current.y][current.x - 1].visited)
        {
            coordinate nextMove;
            nextMove.x = current.x - 1;
            nextMove.y = current.y;
            
            stackOfCoordinate.push(nextMove);
        }
        
        //left top slot
        if (current.y > 0)
        {
            if (grid[current.y - 1][current.x - 1].character == word[stringIndex] && !grid[current.y - 1][current.x - 1].visited)
            {
                coordinate nextMove;
                nextMove.x = current.x - 1;
                nextMove.y = current.y - 1;
                
                stackOfCoordinate.push(nextMove);
                
            }
        }
        
        //left bottom slot
        if (current.y < 3)
        {
            if (grid[current.y + 1][current.x - 1].character == word[stringIndex] && !grid[current.y + 1][current.x - 1].visited)
            {
                coordinate nextMove;
                nextMove.x = current.x - 1;
                nextMove.y = current.y + 1;
                
                stackOfCoordinate.push(nextMove);
            }
        }
    }
    
    //right side
    if (current.x < 3)
    {
        //right slot
        if (grid[current.y][current.x + 1].character == word[stringIndex] && !grid[current.y][current.x + 1].visited)
        {
            coordinate nextMove;
            nextMove.x = current.x + 1;
            nextMove.y = current.y;
            
            stackOfCoordinate.push(nextMove);
        }
        
        //right top slot
        if (current.y > 0)
        {
            if (grid[current.y - 1][current.x + 1].character == word[stringIndex] && !grid[current.y - 1][current.x + 1].visited)
            {
                coordinate nextMove;
                nextMove.x = current.x + 1;
                nextMove.y = current.y - 1;
                
                stackOfCoordinate.push(nextMove);
            }
        }
        
        //right bottom slot
        if (current.y < 3)
        {
            if (grid[current.y + 1][current.x + 1].character == word[stringIndex] && !grid[current.y + 1][current.x + 1].visited)
            {
                coordinate nextMove;
                nextMove.x = current.x + 1;
                nextMove.y = current.y + 1;
                
                stackOfCoordinate.push(nextMove);
            }
        }
    }
    
    //top slot
    if (current.y > 0)
    {
        if (grid[current.y - 1][current.x].character == word[stringIndex] && !grid[current.y - 1][current.x].visited)
        {
            coordinate nextMove;
            nextMove.x = current.x;
            nextMove.y = current.y - 1;
            
            stackOfCoordinate.push(nextMove);
        }
    }
    
    //bottom slot
    if (current.y < 3)
    {
        if (grid[current.y + 1][current.x].character == word[stringIndex] && !grid[current.y + 1][current.x].visited)
        {
            coordinate nextMove;
            nextMove.x = current.x;
            nextMove.y = current.y + 1;
            
            stackOfCoordinate.push(nextMove);
        }
    }
    
    while (!stackOfCoordinate.empty())
    {
        node newGrid[4][4];
        copyGrid(grid, newGrid);
        coordinate nextMove = stackOfCoordinate.top();
        
        newGrid[nextMove.y][nextMove.x].visited = true;
        // printGrid(newGrid);
        
        bool valid(false);
        valid = search(newGrid, stackOfCoordinate.top(), word, stringIndex + 1);
        if (valid)
        {
            while (!stackOfCoordinate.empty())
            {
                stackOfCoordinate.pop();
            }
            return true;
        }
        
        stackOfCoordinate.pop();
        // newGrid[nextMove.y][nextMove.x].visited = false;
    }
    
    return false;
}

bool isNeibour(coordinate a, coordinate b)
{
    if ((abs(a.x - b.x) <= 1) && (abs(a.y - b.y) <= 1))
    {
        return true;
    }
    
    return false;
}

std::stack<coordinate> findFirstCharacter(node grid[4][4], char c)
{
    std::stack<coordinate> stackOfCoordinate;
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (c == grid[i][j].character)
            {
                coordinate coord(j, i);
                stackOfCoordinate.push(coord);
            }
        }
    }
    
    return stackOfCoordinate;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("boggle.in");
    std::ofstream fout("boggle.out");
    
    if (fin.is_open())
    {
//        std::vector< std::vector<char> > grid(6, std::vector<char>(6, '#'));
        node origrinGrid[4][4];
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                char c;
                fin >> c;
                origrinGrid[i][j].character = c;
                
                coordinate cur;
                cur.x = j;
                cur.y = i;
            }
        }
        
        // printGrid(origrinGrid);
        
        while (!fin.eof())
        {
            std::string word;
            fin >> word;
            if (word == "*")
            {
                break;
            }
            
            node gridCopy[4][4];
            copyGrid(origrinGrid, gridCopy);
            std::stack<coordinate> stackofFirstCharCoordinate = findFirstCharacter(gridCopy, word[0]);
            
            bool valid(false);
            while (!stackofFirstCharCoordinate.empty())
            {
                coordinate current = stackofFirstCharCoordinate.top();
                gridCopy[current.y][current.x].visited = true;
                
                
                valid = search(gridCopy, stackofFirstCharCoordinate.top(), word, 1);
                if (valid)
                {
                    while (!stackofFirstCharCoordinate.empty())
                    {
                        stackofFirstCharCoordinate.pop();
                    }
                    break;
                }
                stackofFirstCharCoordinate.pop();
            }
            
            if (valid)
            {
                cout << word << std::setw(22 - int(word.size())) << " VALID" << endl;
                fout << word << std::setw(22 - int(word.size())) << " VALID" << endl;
            }
            else
            {
                cout << word << std::setw(26 - int(word.size())) << " NOT VALID" << endl;
                fout << word << std::setw(26 - int(word.size())) << " NOT VALID" << endl;
            }
            valid = false;
            
        }
    }
    
    fin.close();
    fout.close();
}
