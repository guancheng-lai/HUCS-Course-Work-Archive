//
//  main.cpp
//  COMP 349 #5 Anagrams
//
//  Created by Guancheng Lai on 9/2/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


int main(int argc, const char * argv[])
{
    std::ifstream fin("anagrams.in");
    std::ofstream fout("anagrams.out");
    
    if (fin.good())
    {
        std::string line1;
        std::string line2;
        
        getline(fin, line1);
        getline(fin, line2);
        
        while (fin)
        {
           
            size_t line1Size = line1.size();
            size_t line2Size = line2.size();
            
            for (int i = 0; i < line1Size; i++)
            {
                if (isalpha(line1[i]))
                {
                    line1[i] = toupper(line1[i]);
                }
                else
                {
                    line1.erase(i, 1);
                    line1Size--;
                    i--;
                }


            }

            for (int i = 0; i < line2Size; i++)
            {
                if (isalpha(line2[i]))
                {
                    line2[i] = toupper(line2[i]);
                }
                else
                {
                    line2.erase(i, 1);
                    line2Size--;
                    i--;
                }
            }
            
            std::sort(line1.begin(), line1.end());
            std::sort(line2.begin(), line2.end());
            
            std::cout << line1 << std::endl;
            std::cout << line2 << std::endl;
                
            if (line1 == line2)
            {
                std::cout << "YES" ;
                fout << "YES" ;
            }
            else
            {
                std::cout << "NO" ;
                fout << "NO" ;
            }
            
            
            getline(fin, line1);
            getline(fin, line2);
            
            if (line1 == "<end>" && line2 == "<end>")
            {
                break;
            }
            else
            {
                std::cout << std::endl;
                fout << std::endl;
            }
        }
        
        
    }
}
