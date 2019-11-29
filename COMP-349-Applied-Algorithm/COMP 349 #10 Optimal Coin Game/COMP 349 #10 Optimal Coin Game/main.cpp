//
//  main.cpp
//  COMP 349 #10 Optimal Coin Game
//
//  Created by Guancheng Lai on 9/27/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>


int main(int argc, const char * argv[])
{
    std::ifstream fin("coins.in");
    std::ofstream fout("coins.out");
    
    if (fin.good())
    {
        int numsOfCoins;
        std::vector<int> coins;
        
        fin >> numsOfCoins;
        
        bool firstTime(true);
        while (numsOfCoins != 0)
        {
            if (firstTime) firstTime = false;
            else fout << std::endl;
            
            coins.resize(numsOfCoins);
            for (int i = 0; i < numsOfCoins; i++)
            {
                fin >> coins[i];
            }
            
            std::vector< std::vector<int> > gameboard (numsOfCoins, std::vector<int>(numsOfCoins, 0));
            
            for (int diagonal = 0; diagonal < numsOfCoins; diagonal++)
            {
                for (int row = 0; row <= (numsOfCoins - diagonal - 1); row++)
                {
                    if (diagonal == 0)
                    {
                        gameboard[row][row] = coins[row];
                    }
                    else if (diagonal == 1)
                    {
                        gameboard[row][row + 1] = std::max(coins[row], coins[row + 1]);
                    }
                    else if(diagonal > 1)
                    {
                        int column = row + diagonal;
                        
                        int choice_one_option_one = gameboard[row + 1][column - 1];
                        int choice_one_option_two = gameboard[row + 2][column];
                        int choice_one = coins[row] + std::min(choice_one_option_one, choice_one_option_two);
                        
                        int choice_two_option_one = gameboard[row][column - 2];
                        int choice_two_option_two = gameboard[row + 1][column - 1];
                        int choice_two = coins[column] + std::min(choice_two_option_one, choice_two_option_two);
                        
                        gameboard[row][column] = std::max(choice_one, choice_two);
                    }
                }
            }
            
            fout << gameboard[0][numsOfCoins - 1];
            std::cout << gameboard[0][numsOfCoins - 1] << std::endl;
            
            fin >> numsOfCoins;
            coins.clear();
        }
    }
    
}
