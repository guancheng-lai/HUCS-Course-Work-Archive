//
//  main.cpp
//  COMP 349 #21 HI-Q
//
//  Created by Guancheng Lai on 10/18/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <algorithm>
#include <bitset>
#include <set>
#include <stack>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

const int NUMOFPEGS = 33;
typedef std::bitset<NUMOFPEGS + 1> pegType;
short between[NUMOFPEGS + 1][NUMOFPEGS + 1] {0};

struct jumpType
{
    short from;
    short to;
    jumpType(){}
    jumpType(short f, short t): from(f), to(t){}
};

void initializeBetween()
{
    between[1][3] = between[3][1] = 2;
    between[1][9] = between[9][1] = 4;
    between[2][10] = between[10][2] = 5;
    between[4][6] = between[6][4] = 5;
    between[3][11] = between[11][3] = 6;
    
    between[7][9] = between[9][7] = 8;
    between[8][10] = between[10][8] = 9;
    between[4][16] = between[16][4] = 9;
    between[5][17] = between[17][5] = 10;
    between[9][11] = between[11][9] = 10;
    between[6][18] = between[18][6] = 11;
    between[10][12] = between[12][10] = 11;
    between[11][13] = between[13][11] = 12;
    
    between[7][21] = between[21][7] = 14;
    between[14][16] = between[16][14] = 15;
    between[8][22] = between[22][8] = 15;
    between[15][17] = between[17][15] = 16;
    between[9][23] = between[23][9] = 16;
    between[16][18] = between[18][16] = 17;
    between[10][24] = between[24][10] = 17;
    between[17][19] = between[19][17] = 18;
    between[11][25] = between[25][11] = 18;
    between[18][20] = between[20][18] = 19;
    between[12][26] = between[26][12] = 19;
    between[13][27] = between[27][13] = 20;

    between[21][23] = between[23][21] = 22;
    between[22][24] = between[24][22] = 23;
    between[16][28] = between[28][16] = 23;
    between[23][25] = between[25][23] = 24;
    between[17][29] = between[29][17] = 24;
    between[24][26] = between[26][24] = 25;
    between[18][30] = between[30][18] = 25;
    between[25][27] = between[27][25] = 26;
    
    between[23][31] = between[31][23] = 28;
    between[24][32] = between[32][24] = 29;
    between[28][30] = between[30][28] = 29;
    between[25][33] = between[33][25] = 30;
    between[31][33] = between[33][31] = 32;
}

bool validJump(jumpType jump, pegType pegArrangement)
{
    bool result = false;
    
    if (pegArrangement.test(jump.from) == 1 && pegArrangement.test(jump.to) == 0 && pegArrangement.test(between[jump.from][jump.to]) == 1) {
        result = true;
    }
    
    return result;
}

pegType findNewPegArrangement(jumpType jump, pegType oldPegArrangement)
{
    pegType newPegArrangement(oldPegArrangement);
    
    if (validJump(jump, oldPegArrangement)) {
        newPegArrangement.flip(jump.from);
        newPegArrangement.flip(jump.to);
        newPegArrangement.flip(between[jump.from][jump.to]);
    }
    
    return newPegArrangement;
}


bool marked(pegType pegArrangement, std::set<unsigned long long> &markSet)
{
    bool found = false;
    
    if (markSet.count(pegArrangement.to_ullong()) > 0) {
        found = true;
    }
    
    return found;
}

void mark(pegType pegArrangement, std::set<unsigned long long> &markedSet )
{
    markedSet.insert(pegArrangement.to_ullong());
}

char indexToChar(int i)
{
    char result;
    
    if (i < 10) {
        result = char(i + 48);
    }
    else if (i < 24) {
        result = char(i + 55);
    }
    else {
        result = char(i + 56);
    }
    
    return result;
}


void printSolution(ofstream &fout, std::stack<jumpType> &jumpStack)
{
    while (!jumpStack.empty()) {
        // cout << indexToChar(jumpStack.top().from) << "->" << indexToChar(jumpStack.top().to);
        fout << indexToChar(jumpStack.top().from) << "->" << indexToChar(jumpStack.top().to);
        jumpStack.pop();
        
        if (jumpStack.size() > 0) {
            fout << " ";
        }
    }
}

bool findSolution(pegType currentPegArrangement, std::set<unsigned long long> &markedSet, pegType solutionPegArrangement, std::stack<jumpType> &jumpStack)
{
    bool solved = false;
    
    if (currentPegArrangement == solutionPegArrangement) {
        solved = true;
    } else {
        mark(currentPegArrangement, markedSet);
        
        for (short from = 1; from <= NUMOFPEGS && !solved; ++from) {
            for (short to = 1; to <= NUMOFPEGS && !solved; ++to) {
                jumpType jump { from, to };
                pegType newPegArr = findNewPegArrangement(jump, currentPegArrangement);
                if (!marked(newPegArr, markedSet)) {
                    solved = findSolution(newPegArr, markedSet, solutionPegArrangement, jumpStack);
                    if (solved) {
                        jumpStack.push(jump);
                    }
                }
            }
        }
    }
    
    return solved;
}

int toIndex(char c)
{
    int result;
    
    if (isdigit(c)) {
        result = int(c) - '0';
    }
    else if (c > 'O') {
        result = int(c) - '0' - 8;
    }
    else {
        result = int(c) - '0' - 7;
    }
    
    return result;
}

int main(int argc, const char * argv[])
{
    ifstream fin("hiq.in");
    bool firstTime = true;
    if (fin.good())
    {
        ofstream fout("hiq.out");
        initializeBetween();
        
        char startPosition_char;
        fin >> startPosition_char;
        
        while (startPosition_char != '0') {
            if (firstTime) {
                firstTime = false;
            }
            else{
                fout << endl;
            }
            
            int startPosition = toIndex(startPosition_char);

            pegType start; start.set(); start.flip(0); start.flip(startPosition);
            pegType solved; solved.reset(); solved.flip(startPosition);

            std::stack<jumpType> jumpStack;
            std::set<unsigned long long> markedSet;
            
            if (findSolution(start, markedSet, solved, jumpStack)) {
                printSolution(fout, jumpStack);
            } else {
                fout << "No solution for hole at " << startPosition_char ;
                // cout << "No solution for hole at " << startPosition_char ;
            }

            markedSet.clear();
            fin.ignore();
            fin >> startPosition_char;
        }
    }


}
