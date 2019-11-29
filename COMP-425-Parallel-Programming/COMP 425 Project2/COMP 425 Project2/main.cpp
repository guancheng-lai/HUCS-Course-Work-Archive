//
//  main.cpp
//  COMP 425 Project2
//
//  Created by Guancheng Lai on 10/10/18.
//  Copyright � 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>
#include <chrono>

using std::cin;
using std::endl;
using std::cout;
using std::vector;

double minOf(double a, double b)
{
	return a < b ? a : b;
}

void allPairAlgorithm(vector<vector<double> > &timeSheet, int numOfLocations)
{
	for (int middle = 0; middle < numOfLocations; ++middle) {
		double * middleDistance = timeSheet[middle].data();
		for (int start = 0; start < numOfLocations; ++start) {
			double * startDistance = timeSheet[start].data();
			for (int destination = 0; destination < numOfLocations; ++destination) {
				timeSheet[start][destination] = minOf(startDistance[destination], startDistance[middle] + middleDistance[destination]);		
			}
		}
	}
}

void calculateResult(int numOfRoutes, vector<vector<int> > &listOfRoutes, const vector<vector<double> > &timeSheet)
{
	double minimunWeight(std::numeric_limits<double>::max());
    
	vector<double> results(numOfRoutes);
    
	for (int i = 0; i < numOfRoutes; ++i) {
		int numOfPointsToVisit;
		cin >> numOfPointsToVisit;

		listOfRoutes[i].resize(numOfPointsToVisit);

		if (numOfPointsToVisit > 1) {
			for (int j = 0; j < numOfPointsToVisit; ++j) {
				cin >> listOfRoutes[i][j];
			}
		}

		double totalWeight(0);

#pragma omp parallel for reduction (+ : totalWeight)
		for (int j = 1; j < numOfPointsToVisit; ++j) {
			int from = listOfRoutes[i][j - 1];
			int to = listOfRoutes[i][j];
			double singleWeight = timeSheet[from][to];
			totalWeight += singleWeight;
		}

		if (totalWeight < minimunWeight) {
			minimunWeight = totalWeight;
		}

		results[i] = totalWeight;
	}

	for (int i = 0; i < numOfRoutes; i++) {
		cout << results[i] << endl;
	}

	cout << minimunWeight << endl;
}

void getMapData(int numOfLocations, vector<vector<double> > &timeSheet)
{
	if (numOfLocations > 0) {
		int numOfPaths;
		cin >> numOfPaths;

		for (int i = 0; i < numOfPaths; ++i) {
			int from, to, weight;
			cin >> from >> to >> weight;
			timeSheet[from][to] = weight;
		}
	}
}

int main(int argc, const char * argv[])
{
	int numOfLocations;
	cin >> numOfLocations;
	
	vector<vector<double> > timeSheet(numOfLocations, vector<double>(numOfLocations, std::numeric_limits<double>::max()));

#pragma omp parallel for
	for (int i = 0; i < numOfLocations; ++i) {
		timeSheet[i][i] = 0.0;
	}
	
	getMapData(numOfLocations, timeSheet);
	allPairAlgorithm(timeSheet, numOfLocations);

	int numOfRoutes;
	cin >> numOfRoutes;
	vector<vector<int> > listOfRoute(numOfRoutes);

	if (numOfLocations > 0 && numOfRoutes > 0) {
		calculateResult(numOfRoutes, listOfRoute, timeSheet);
	}
}
