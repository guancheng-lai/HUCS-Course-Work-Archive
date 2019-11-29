//
//  main.cpp
//  COMP 349 #Flip Pancakes
//
//  Created by Guancheng Lai on 10/31/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <set>
using std::queue;
using std::string;
using std::set;
using std::cout;
using std::cin;
using std::endl;

struct CakeInfo
{
    string cakes;
    int numOfMoves;
    CakeInfo(){}
    CakeInfo(string ckes, int nMoves) : cakes(ckes), numOfMoves(nMoves) {}
};

string getAnswer (string cakes)
{
    string result = cakes;
    
    for (auto it = result.begin(); it != result.end(); it++) {
        *it = isupper(*it) ? *it :toupper(*it);
    }
    std::sort(result.begin(), result.end());
    
    
    return result;
}

string flip (const string cakes, size_t flipNumCakes)
{
    if (flipNumCakes == 0) {
        return cakes;
    }
    
    string result;
    
    int remain = int(cakes.size()) - int(flipNumCakes);
    auto it = cakes.begin();
    for (int i = 0; i < remain; ++i) {
        result += *it;
        it++;
    }
    
    auto rit = cakes.rbegin();
    for (int i = 0; i < flipNumCakes; ++i) {
        if (isupper(*rit)) {
            result += tolower(*rit);
        }
        else {
            result += toupper(*rit);
        }
        
        rit++;
    }

    
    return result;
}

void searching (size_t index, CakeInfo currentCakesInfo, queue<CakeInfo> &queueOfFlips, set<string> &previousFlips)
{
    string newFlip = flip(currentCakesInfo.cakes, index);
    CakeInfo newCakeInfo(newFlip, currentCakesInfo.numOfMoves + 1);
    
    if (previousFlips.count(newFlip) == 0) {
        previousFlips.insert(newFlip);
        queueOfFlips.push(newCakeInfo);
    }
}

void BFS (queue<CakeInfo> &queueOfFlips, set<string> &previousFlips, CakeInfo currentCakeInfo, string answer, int &totalMoveMakes)
{
    size_t length = answer.size();
    while (!queueOfFlips.empty()) {
        currentCakeInfo = queueOfFlips.front();
        queueOfFlips.pop();
        
        if (currentCakeInfo.cakes == answer) {
            totalMoveMakes = currentCakeInfo.numOfMoves;
            break;
        }
        
        for (size_t i = 1; i <= length; ++i) {
            searching(i, currentCakeInfo, queueOfFlips, previousFlips);
        }
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("pancakes.in");
    
    if (fin.good()) {
        std::ofstream fout("pancakes.out");
        string cakes;
        getline(fin, cakes);
        bool isFirstTime = true;
        while (cakes != "0") {
            if (isFirstTime) {
                isFirstTime = false;
            } else {
                fout << endl;
            }
            
            CakeInfo currentCakesInfo(cakes, 0);
            string answer = getAnswer(cakes);
            queue<CakeInfo> queueOfFlips;
            queueOfFlips.push(currentCakesInfo);
            set<string> previousFlips;
            previousFlips.insert(currentCakesInfo.cakes);
            int totalMoveMakes = 0;
            
            BFS(queueOfFlips, previousFlips, currentCakesInfo, answer, totalMoveMakes);
            
            fout << totalMoveMakes;
            getline(fin, cakes);
        }
    }



}
