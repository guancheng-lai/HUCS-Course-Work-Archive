//
//  main.cpp
//  COMP 349 #32 Jungle Roads
//
//  Created by Guancheng Lai on 10/25/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::priority_queue;

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

struct Edge
{
    int a;
    int b;
    int weight;
    Edge(int pointA, int pointB, int w) : a(pointA), b(pointB), weight(w) {}
};

struct compare
{
    bool operator()(const Edge &l, const Edge &r) {
        return l.weight > r.weight;
    }
};

void printPQ(const priority_queue<Edge, vector<Edge>, compare>  &pq)
{
    priority_queue<Edge, vector<Edge>, compare> pqOfEdges(pq);
    
    while (!pqOfEdges.empty()) {
        std::cout << pqOfEdges.top().a << " - " << pqOfEdges.top().b << " = " << pqOfEdges.top().weight << std::endl;
        pqOfEdges.pop();
    }
    std::cout << std::endl;
}

void printQueue(const queue<Edge> &queueOfEdge)
{
    queue<Edge> q(queueOfEdge);
    int total(0);
    
    while (!q.empty()) {
      std::cout << q.front().a << " - " << q.front().b << " = " << q.front().weight << std::endl;
        total += q.front().weight;
        q.pop();
    }
    std::cout << "Total = " << total << std::endl << std::endl;
}

void outputMSTWeight(std::ofstream &fout, const queue<Edge> &mst)
{
    int total(0);
    
    queue<Edge> minimunSpanningTree(mst);
    while (!minimunSpanningTree.empty()) {
        total += minimunSpanningTree.front().weight;
        minimunSpanningTree.pop();
    }
    
    fout << total;
}

void buildMST(priority_queue<Edge, vector<Edge>, compare> &pqOfEdges, queue<Edge> &mst, int numOfVertex, UnionFind &uf)
{
    while (!pqOfEdges.empty() && mst.size() < numOfVertex - 1) {
        Edge edge = pqOfEdges.top();
        pqOfEdges.pop();
        if (uf.find(edge.a) != uf.find(edge.b)) {
            uf.unite(edge.a, edge.b);
            mst.push(edge);
        }
    }
}

void getInput(int numOfVertex, std::ifstream &fin, priority_queue<Edge, vector<Edge>, compare> &pqOfEdges)
{
    for (int i = 0; i < numOfVertex - 1; i++) {
        char current;
        fin >> current;int numOfVillagesToGo;
        fin >> numOfVillagesToGo;
        
        for (int j = 0; j < numOfVillagesToGo; j++) {
            char village;
            fin >> village;
            int weight;
            fin >> weight;
            
            Edge edge(int(current) - 65, int(village) - 65, weight);
            pqOfEdges.push(edge);
        }
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("jungle.in");
    
    if (fin.good()) {
        std::ofstream fout("jungle.out");
        bool firstTime = true;
        int numOfVertex;
        fin >> numOfVertex;
        
        while (numOfVertex != 0) {
            if (firstTime) {
                firstTime = false;
            } else {
                fout << std::endl;
            }
            
            queue<Edge> mst;
            priority_queue<Edge, vector<Edge>, compare> pqOfEdges;
            UnionFind uf(numOfVertex);
            
            getInput(numOfVertex, fin, pqOfEdges);
            buildMST(pqOfEdges, mst, numOfVertex, uf);
            outputMSTWeight(fout, mst);
            
            fin >> numOfVertex;
        }
    }
}
