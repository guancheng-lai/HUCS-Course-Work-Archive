//
//  AI.cpp
//  NIM Project AI part
//
//
//  IN:     vector<int> gameboard
//  OUT:    string "row/rocks"
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

const int MAX_ROW_NUM_IN_BINARY = 5;

std::string botMove(vector<int>);
int convertToBinary(int);
string NIMaddUp(int[]);
bool checkBalance(vector<int>, string);
string findMove(vector<int>, int[], string);
int findLargestUnbalance(string);
int findLargestToSubtract(vector<int>, int);
int findMostRocks(vector<int>);

int main(int argc, const char * argv[]) {
    vector<int> gameboard;
    
    gameboard.push_back(1);


    
    std::string a = botMove(gameboard);
    cout << a << endl;
    
    while(!gameboard.empty())
    {
        gameboard.pop_back();
    }
    
    gameboard.push_back(1);
    gameboard.push_back(7);
    gameboard.push_back(18);
    gameboard.push_back(20);
    
    a = botMove(gameboard);
    cout << a << endl;
    return 0;
}


std::string botMove(vector<int> gameboard)
{
    vector<int> temp(gameboard);
    string result = "";
    int binaryValue[20];
    
    for(unsigned i = 0; i < temp.size(); i++)
    {
        binaryValue[i] = convertToBinary(temp[i]);
    }
    
    string binarySum = NIMaddUp(binaryValue);
    string move;
    if (binarySum.find("1") != string::npos)    //check if balance
    {
        //if no balance, find a move to balance
        move = findMove(temp, binaryValue, binarySum);
    }
    else
    {
        int rowToSubtract = findMostRocks(temp) + 1;
        move = std::to_string(rowToSubtract) + "01";
    }
    
    return move;
}

int convertToBinary(int value)
{
    if(value == 0)
    {
        return 0;
    }
    
    if(value == 1)
    {
        return 1;
    }
    
    //Largest value comes in will be 20 which is 10100
    //Need 5 slot for the binary value
    
    int binaryNumber[MAX_ROW_NUM_IN_BINARY];
    for(int i = 0; i < MAX_ROW_NUM_IN_BINARY; i++)
    {
        binaryNumber[i] = 0;
    }
    
    //Convert
    int i = 0;
    while (value > 0)
    {
        binaryNumber[i] = value % 2;
        value = value / 2;
        i++;
    }
    
    //Convert the array to an integer and return
    std::reverse(std::begin(binaryNumber), std::end(binaryNumber));
    string binaryNumString;
    for(int i = 1; i < MAX_ROW_NUM_IN_BINARY; i++)
    {
        binaryNumString += std::to_string(binaryNumber[i]);
    }
    int result = atoi(binaryNumString.c_str());
    return result;
}

string NIMaddUp(int binaryValue[])
{
    //digit[0] is alwasy empty
    //strats at digit[1] to [4]
    int digit[6] = {0, 0, 0, 0, 0, 0};
    string sum;
    for(int i = 0; i < 20 && binaryValue[i] >= 0 && binaryValue[i] <= 10100; i++)
    {
        if(binaryValue[i] % 10 == 1)
        {
            digit[1]++;
        }
        
        if(binaryValue[i] % 100 >= 10)
        {
            digit[2]++;
        }
        
        if(binaryValue[i] % 1000 >= 100)
        {
            digit[3]++;
        }
        
        if(binaryValue[i] % 10000 >= 1000)
        {
            digit[4]++;
        }
        
        if (binaryValue[i] % 100000 >= 10000)
        {
            digit[5]++;
        }
    }
    
    if (digit[5] % 2 == 0)
    {
        sum += "0";
    }
    else
    {
        sum += "1";
    }
    
    if (digit[4] % 2 == 0)
    {
        sum += "0";
    }
    else
    {
        sum += "1";
    }
    
    if (digit[3] % 2 == 0)
    {
        sum += "0";
    }
    else
    {
        sum += "1";
    }
    
    if (digit[2] % 2 == 0)
    {
        sum += "0";
    }
    else
    {
        sum += "1";
    }
    
    if(digit[1]%2 == 0)
    {
        sum += "0";
    }
    else
    {
        sum += "1";
    }
    
    return sum;
}

bool checkBalance(vector<int> gameboard)
{
    bool result = false;
    
    int tempBinaryValue[20];
    for(unsigned i = 0; i < gameboard.size(); i++)
    {
        tempBinaryValue[i] = convertToBinary(gameboard[i]);
    }
    
    if(NIMaddUp(tempBinaryValue).find("1") == string::npos)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    
    return result;
}

string findMove(vector<int> gameboard, int binaryValue[], string binarySum)
{
    int largestUnbalance = findLargestUnbalance(binarySum);
    int rowToSubtract = 0;
    
    rowToSubtract = findLargestToSubtract(gameboard, largestUnbalance);
    
    int stoneToSubtract = 0;
    while (!checkBalance(gameboard))
    {
        gameboard[rowToSubtract] += stoneToSubtract;
        stoneToSubtract++;
        gameboard[rowToSubtract] -= stoneToSubtract;
    }
    
    string result = std::to_string(rowToSubtract + 1);
    if (stoneToSubtract < 10)
    {
        result += '0';
    }
    result += std::to_string(stoneToSubtract);
    
    //cout << "Remove from array[" << result.substr(0, result.find("/")) << "], remove " << result.substr(result.find("/") + 1) << " rocks" << std::endl;
    
    return result;
}

int findLargestToSubtract(vector<int> gameboard, int largestValue)
{
    int result = -1;
    bool found = false;
    for (unsigned i = 0; i < gameboard.size() && !found; i++)
    {
        //Convert to binary
        int tempBinaryValue = convertToBinary(gameboard[i]);
        
        //switch by largestValue
        switch (largestValue)
        {
            case 16:
                if(tempBinaryValue % 100000 >= 10000)
                {
                    result = i;
                    found = true;
                }
                break;
            case 8:
                if(tempBinaryValue % 10000 >= 1000)
                {
                    result = i;
                    found = true;
                }
                break;
            case 4:
                if(tempBinaryValue % 1000 >= 100)
                {
                    result = i;
                    found = true;
                }
                break;
            case 2:
                if(tempBinaryValue % 100 >= 10)
                {
                    result = i;
                    found = true;
                }
                break;
            case 1:
                if(tempBinaryValue % 10 >= 1)
                {
                    result = i;
                    found = true;
                }
                break;
                
        }
    }
    return result;
}

int findLargestUnbalance(string value)
{
    int result;
    int position = int(value.find("1") + 1);
    //The largest Unbalance is the digit position of the NIM sum
    //Start at 1, end at 5
    switch (position) {
        case 1:
            result = 16;
            break;
        case 2:
            result = 8;
            break;
        case 3:
            result = 4;
            break;
        case 4:
            result = 2;
            break;
        case 5:
            result = 1;
            break;
        default:
            result = 0;
            cout << "Unsupported." << endl;
            break;
    }
    
    return result;
}

int findMostRocks(vector<int> gameboard)
{
    int result = -1;
    
    int mostRock = 0;
    for (unsigned i = 0; i < gameboard.size(); i++)
    {
        if (gameboard[i] >= mostRock)
        {
            mostRock = gameboard[i];
            result = i;
        }
    }
    
    return result;
}
