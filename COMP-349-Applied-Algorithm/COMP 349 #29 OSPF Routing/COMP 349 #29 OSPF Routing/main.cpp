//
//  main.cpp
//  COMP 349 #29 OSPF Routing
//
//  Created by Guancheng Lai on 11/15/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <functional>
using std::vector;
using std::string;
using std::priority_queue;
using std::set;
using std::cout;
using std::endl;
using std::pair;

bool greaterPair ( const pair<long double, int> &p1, const pair<long double, int> &p2)
{
    return p1.first > p2.first;
}

//auto comp = [] (const pair<long double, int> &p1, const pair<long double, int> &p2) -> bool { return p1.first >= p2.first; };

typedef priority_queue< pair<long double, int>, vector< pair<long double, int> >, std::function<bool(pair<long double, int>, pair<long double, int>)> > minPriorityQueue;
constexpr long double VERY_LARGE = 99999999999;

void printAdjMatrix(const vector<vector<long double> > &matrix)
{
    size_t length = matrix.size() - 1;
    for (int i = 1; i <= length; ++i) {
        for (int j = 1; j <= length; ++j) {
            cout << std::setw(12) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void output_result(std::ostream &out, const vector<long double> &distance, int start)
{
    size_t size = distance.size();
    out << start << ":";
    for (int i = 1; i < size; ++i) {
        if (i == start) continue;
        
        out << " " << i << "(";
        out << std::fixed << std::setprecision(2) << distance[i];
        out << ")";
    }

}

void read_in_from_file(int size, std::ifstream &fin, vector< vector<long double> > &adjacencyMatrix)
{
    for (int i = 1; i <= size; ++i) {
        for (int j = 1; j <= size; ++j) {
            long double distance;
            fin >> distance;
            
            if (i == j) {
                adjacencyMatrix[i][j] = 0;
            }
            else {
                adjacencyMatrix[i][j] = (distance == 0) ? VERY_LARGE : (100000000.0 / distance);
            }
        } // end of inner loop
    } // end of outer loop
}

void initialize_minHeap(int size, int start, const vector<long double> &distance, minPriorityQueue &minHeap)
{
    for (int i = 1; i <= size; ++i) {
        if (distance[i] != VERY_LARGE) {
            if (i != start) {
                minHeap.push(pair<long double, int>(distance[i], i));
            }
        }
    }
}

void dijkstra (int size, set<int> &V, set<int> accessed, vector<long double> &distance, vector<int> &parent, vector< vector<long double> > &adjacencyMatrix, minPriorityQueue minHeap)
{
    while (V.size() != accessed.size()) {
        int selected = minHeap.top().second;
        minHeap.pop();
        if (accessed.count(selected) > 0) continue;
        
        accessed.insert(selected);
        for (int i = 1; i <= size; ++i) {
            if (accessed.count(i) != 0) continue;
            
            if (distance[selected] + adjacencyMatrix[selected][i] < distance[i]) {
                distance[i] = distance[selected] + adjacencyMatrix[selected][i];
                minHeap.push(pair<long double, int>(distance[i], i));
                parent[i] = selected;
            }
        }
        
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("ospf.in");
    if (fin.good()) {
        std::ofstream fout("ospf.out");
        bool first_time = true;
        
        int size;
        fin >> size;
        while (size != 0) {
            vector< vector<long double> > adjacencyMatrix(size + 1, vector<long double>(size + 1));
            read_in_from_file(size, fin, adjacencyMatrix);
//            printAdjMatrix(adjacencyMatrix);
            
            set<int> V;
            for (int i = 1; i <= size; ++i) { V.insert(i); }
            
            int start;
            fin >> start;
            while (start > 0) {
                set<int> accessed;
                accessed.insert(start);
                
                vector<int> parent(size + 1, -1);
                parent[start] = start;
                
                vector<long double> distance(size + 1, VERY_LARGE);
                for (int i = 1; i <= size; ++i) { distance[i] = adjacencyMatrix[start][i]; }
            
                minPriorityQueue minHeap(greaterPair);
                initialize_minHeap(size, start, distance, minHeap);
                
                dijkstra(size, V, accessed, distance, parent, adjacencyMatrix, minHeap);
                
                if (first_time) {
                    first_time = false;
                }
                else {
                    fout << endl;
                    cout << endl;
                }
                
                output_result(cout, distance, start);
                output_result(fout, distance, start);
                
                fin >> start;
            }
    
            fin >> size;
            
            if (size != 0) {
                cout << endl << "*****" ;
                fout << endl << "*****" ;
            }
        } // end of while, single set of data
    }
}
