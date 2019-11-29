//
//  main.cpp
//  COMP 349 #3 Count Your Cousins
//
//  Created by Guancheng Lai on 9/1/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

int main(int argc, const char * argv[])
{
    std::ifstream fin("cousins.in");
    std::ofstream fout("cousins.out");
    
    bool first(true);
    if (fin.good())
    {
        while (!fin.eof())
        {
            int total(0);
            int interest(0);
            fin >> total >> interest;
            if (total == 0 && interest == 0)
            {
                break;
            }
            
            if (!first) fout << endl;
            
            first = false;
            
            fin.ignore();
            
            std::vector<int> parents;
            std::vector<int> childs;
            
            int data;
            fin >> data;
            childs.push_back(data);
            parents.push_back(-1);
            
            int currentPerentIndex(-1);
            int readDataIndex(0);
            while (readDataIndex < total - 1 && fin.good())
            {
                fin >> data;
                childs.push_back(data);
                
                if (childs[readDataIndex] + 1 != data)
                {
                    currentPerentIndex++;
                }
                
                parents.push_back(currentPerentIndex);
                readDataIndex++;
            }
            
            
            long interestIndex = std::distance(childs.begin(), std::find(childs.begin(), childs.end(), interest));
            if (interestIndex == 0 || parents[interestIndex] == -1)
            {
                fout << 0;
               
            }
            else if (parents[parents[interestIndex]] == -1)
            {
                fout << 0;
            }
            else
            {
                int father = childs[parents[interestIndex]];
                int grandParent = childs[parents[parents[interestIndex]]];
                
                int count(0);
                int startIndex(0);
                for (int i = 0; i < childs.size(); i++)
                {
                    if (parents[i] != -1)
                    {
                        startIndex = i;
                        break;
                    }
                }
                
                for (int i = startIndex; i < childs.size() && parents[i] >= 0; i++)
                {
                    if (parents[parents[i]] != -1)
                    {
                        if (childs[parents[parents[i]]] == grandParent && childs[parents[i]] != father)
                        {
                            count++;
                        }
                    }
                }
                fout << count;
            }
        }
        
        
        
        fin.close();
        fout.close();
    }
}
