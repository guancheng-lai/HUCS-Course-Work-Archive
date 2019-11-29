//
//  main.cpp
//  COMP 349 #10 Cash Cow
//
//  Created by Guancheng Lai on 10/9/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <queue>

const int ROW = 12;
const int COL = 10;

class UnionFind
{
    std::vector <int> setName;
    std::vector <int> setSize;
    
public:
    UnionFind(int n) {            // Constructor used to create initial n sets
        setSize.resize(n,1);    // Initialize each set's size to 1
        
        setName.resize(n);        // Initialize the "name" of each singleton set
        for (int i=0; i<n; i++) {
            setName[i] = i;
        }
    }
    
    ~UnionFind() {                // Destructor should release the memory allocated
        setName.clear();
        setSize.clear();
    }
    
    int find (int p) {        // Find the name of the set that contains element p
        while (p != setName[p]) {
            setName[p] = setName[setName[p]];    // Compression step
            p = setName[p];
        }
        return p;
    }
    
    void unite ( int x, int y) {    // Unite the sets that contain x & y
        // Note: The name 'unite' is used to avoid confusion with the union keyword
        int i = find(x);
        int j = find(y);
        if (i != j) {        // If x & y are in the same set, nothing to do
            
            // Smaller set is added to the larger of the 2 sets
            if (setSize[i] < setSize[j]) {
                setName[i] = j;
                setSize[j] += setSize[i];
            } else {
                setName[j] = i;
                setSize[i] += setSize[j];
            }
        }
    }
    
    int size( int x ) {                // return size of set associated with x
        return setSize[find(x)];
    }
    
    void clear() {                    // Method used to explicitly release allocated memory
        setName.clear();
        setSize.clear();
    }
};

struct Node
{
    char color;
    int row;
    int col;
    int id;
    Node(){}
    Node(char c, int r, int column) : color(c), row(r), col(column){ id = (r - 1) * 10 + column; }
};

void printUnionID(UnionFind * uf, std::vector< std::vector<Node> > &gameboard)
{
    for (int i = ROW; i > 0; i--) {
        for (int j = 1; j <= COL; j++) {
            std::cout << std::setw(3) << (*uf).find(gameboard[i][j].id) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printGameboard(const std::vector< std::vector<Node> > &gameboard)
{
    for (int i = ROW; i > 0; i--) {
        for (int j = 1; j <= COL; j++) {
            std::cout << gameboard[i][j].color << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void checkAround(UnionFind *uf, const std::vector< std::vector<Node> > &gameboard, int row, int column)
{
    if (column > 1 && gameboard[row][column].color == gameboard[row][column - 1].color) {
        (*uf).unite(gameboard[row][column].id, gameboard[row][column - 1].id);
    }
    
    if (column < COL && gameboard[row][column].color == gameboard[row][column + 1].color) {
        (*uf).unite(gameboard[row][column].id, gameboard[row][column + 1].id);
    }
    
    if (row > 1 && gameboard[row][column].color == gameboard[row - 1][column].color) {
        (*uf).unite(gameboard[row][column].id, gameboard[row - 1][column].id);
    }
    
    if (row < ROW && gameboard[row][column].color == gameboard[row + 1][column].color) {
        (*uf).unite(gameboard[row][column].id, gameboard[row + 1][column].id);
    }
}

void unionGameboard(const std::vector< std::vector<Node> > &gameboard, UnionFind * uf)
{
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            if (gameboard[i][j].color != ' ') {
                checkAround(uf, gameboard, i, j);
            }
        }
    }
}

void squeeze(std::vector< std::vector<Node> > &gameboard)
{
    std::queue<int> columnsHaveElement;
    
    for (int j = 1; j <= COL; j++) {
        if (gameboard[1][j].color != ' ') {
            columnsHaveElement.push(j);
        }
    }

    
    size_t numOfCOlRemain = columnsHaveElement.size();
    int index(1);
    while (!columnsHaveElement.empty()) {
        int col = columnsHaveElement.front();
        
        for (int i = 1; i <= ROW; i++) {
            gameboard[i][index].color = gameboard[i][col].color;
        }
        
        columnsHaveElement.pop();
        index++;
    }
    
    std::cout << numOfCOlRemain << std::endl;
    if (numOfCOlRemain > 0) {
        for (size_t i = numOfCOlRemain + 1; i <= COL; i++) {
            for (int j = 1; j <= ROW; j++) {
                gameboard[j][i].color = ' ';
            }
        }
    }
}

void fallOff(std::vector< std::vector<Node> > &gameboard, int &numOfRest)
{
    for (int i = 1; i <= COL; i++) {
        std::vector<char> rest(ROW, ' ');
        int index(0);
        for (int j = 1; j <= ROW; j++) {
            if (gameboard[j][i].color != ' ') {
                rest[index] = gameboard[j][i].color;
                index++;
            }
        }
        
        for (int rows = 0; rows <= ROW; rows++) {
            gameboard[rows + 1][i].color = rest[rows];
        }
        
        numOfRest += index;
    }
}

int updateGameboard(std::vector< std::vector<Node> > &gameboard)
{
    int numOfRest(0);
    
    fallOff(gameboard, numOfRest);
    squeeze(gameboard);
    
    return numOfRest;
}

void makeMove(std::vector< std::vector<Node> > &gameboard, UnionFind * uf, int column, int row)
{
    if (gameboard[row][column].color == ' ') {
        return ;
    }
    
    int idToMove = (*uf).find(gameboard[row][column].id);
    
    if ((*uf).size(idToMove) <= 2) {
        return ;
    }
    
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            if ((*uf).find(gameboard[i][j].id) == idToMove) {
                gameboard[i][j].color = ' ';
            }
        }
    }
}

void inputFromFile(std::ifstream &fin, int &numOfMoves, std::vector< std::vector<Node> > &gameboard, std::queue< std::pair<char, int> > &queueOfMoves, UnionFind * uf)
{
    fin.ignore();
    for (int row = ROW; row > 0; row--) {
        std::string line;
        getline(fin, line);
        for (int col = 1; col <= COL; col++) {
            Node node(line[col - 1], row, col);
            gameboard[row][col] = node;
        }
    }
    
    for (int i = 0; i < numOfMoves; i++) {
        char col;
        int row;
        fin >> col >> row;
        queueOfMoves.push(std::pair<char, int>(col, row));
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("cashcow.in");
    std::ofstream fout("cashcow.out");
    
    if (fin.good()) {
        int numOfMoves;
        fin >> numOfMoves;
        
        while (numOfMoves > 0) {
            std::vector< std::vector<Node> > gameboard(ROW + 2, std::vector<Node>(COL + 2));
            std::queue< std::pair<char, int> > queueOfMoves;
            UnionFind * uf = new UnionFind ((ROW + 1) * COL);
            
            inputFromFile(fin, numOfMoves, gameboard, queueOfMoves, uf);
            unionGameboard(gameboard, uf);
            // printGameboard(gameboard);
            // printUnionID(uf, gameboard);
            
            int numOfRemain(0);
            while (!queueOfMoves.empty()) {
                int column_move = int(queueOfMoves.front().first) - 'a' + 1;
                int row_move = queueOfMoves.front().second;
                
                makeMove(gameboard, uf, column_move, row_move);
                // printGameboard(gameboard);
                // printUnionID(uf, gameboard);
                numOfRemain = updateGameboard(gameboard);
                delete uf;
                uf = new UnionFind ((ROW + 1) * COL);
                // printGameboard(gameboard);
                // printUnionID(uf, gameboard);
                unionGameboard(gameboard, uf);
                // printGameboard(gameboard);
                // printUnionID(uf, gameboard);
                queueOfMoves.pop();
            }
            
            fin >> numOfMoves;
            fout << numOfRemain << std::endl;
        }
    }
}
