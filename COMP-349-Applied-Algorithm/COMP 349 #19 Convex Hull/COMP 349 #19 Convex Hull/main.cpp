//
//  main.cpp
//  COMP 349 #19 Convex Hull
//
//  Created by Guancheng Lai on 10/30/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <numeric>
#include <math.h>

using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::stack;
using std::priority_queue;

typedef pair<double, double> Point;
const double EPSILON = 0.0000001;
Point origin;

bool compare_pair (const pair<double, double> &a, const pair<double, double> &b)
{
    return a.first <= b.first;
}

double findAngle(const Point &a, const Point &b)
{
    return atan2(b.second - a.second, b.first - a.first);
}

bool sortByAngel(const Point &a, const Point &b)
{
    return (findAngle(origin, a) < findAngle(origin, b));
}

bool sortBySecond(const Point &a, const Point &b)
{
    return (a.second < b.second);
}

bool nonLeftTurn(Point p1, Point p2, Point p3)
{
    // "NonLeftTurn" means a turn to the right OR no turn at all
    // Computed value will be positive if p3 is to the left of line <p1,p2>,
    // negative if p3 is to the right, and 0 if the three points are collinear.
    
    double value = (p1.first * p2.second + p3.first * p1.second + p2.first * p3.second - p3.first * p2.second - p2.first * p1.second - p1.first * p3.second);
    return (value < EPSILON);
}

double getDistance(Point a, Point b)
{
    return sqrt((b.second - a.second)*(b.second - a.second) + (b.first - a.first)*(b.first - a.first));
}

Point furthestPoint (const vector<Point> &points)
{
    Point result;
    double furthest_distance = -std::numeric_limits<double>::infinity();
    
    for (int i = 0; i < points.size(); ++i) {
        double distance = getDistance(points[i], origin);
        if (distance > furthest_distance) {
            furthest_distance = distance;
            result = points[i];
        }
    }
    
    return result;
}

vector<Point> removeDuplicatePointWithSameAngle(vector<Point> &points)
{
    vector<Point> result;
    if (points.size() < 3) {
        return result;
    }
    result.push_back(points[0]);

    vector<Point> same_angle;
    for (int i = 1; i < points.size() - 1; ++i) {
        if (findAngle(origin, points[i]) == findAngle(origin, points[i + 1])) {
            same_angle.push_back(points[i]);
            same_angle.push_back(points[i + 1]);
            continue;
        }
        else {
            if (!same_angle.empty()) {
                result.push_back(furthestPoint(same_angle));
                same_angle.clear();
            }
            
            result.push_back(points[i]);
        }
    }
    
    result.push_back(points[points.size() - 1]);
    return result;
}

void printListOfPoints(const vector<Point> &list, int index ,std::ostream &out)
{
    out << "Set #" << index << ":";
    for (int i = 0; i < list.size(); ++i) {
        out << " (" << list[i].first << "," << list[i].second << ")";
    }
}

void calculatintConvexHull(const vector<Point> &points, stack<Point> &result_stack)
{
    for (int i = 3; i < points.size(); ++i) {
        Point top = result_stack.top();
        result_stack.pop();
        Point nextToTop = result_stack.top();
        result_stack.push(top);
        
        while (nonLeftTurn(nextToTop, top, points[i])) {
            result_stack.pop();
            
            top = result_stack.top();
            result_stack.pop();
            nextToTop = result_stack.top();
            result_stack.push(top);
        }
        
        result_stack.push(points[i]);
    }
}

void noEnoughPoints(std::ifstream &fin, std::ofstream &fout, const vector<Point> &p, int &index, int &numOfPoints)
{
    printListOfPoints(p, index, cout);
    printListOfPoints(p, index, fout);
    index++;
    fin >> numOfPoints;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("convex.in");
    if (fin.good()) {
        std::ofstream fout("convex.out");
        bool first_time = true;
        int index = 1;
        int numOfPoints;
        fin >> numOfPoints;
        while (numOfPoints > 0) {
            if (first_time) { first_time = false; }
            else {fout << endl; }
            
            vector<Point> listOfPoints(numOfPoints);
            for (int i = 0; i < numOfPoints; ++i) {
                fin >> listOfPoints[i].first;
                fin >> listOfPoints[i].second;
            }
            
            std::sort(listOfPoints.begin(), listOfPoints.end(), sortBySecond);
            origin = listOfPoints[0];
            std::sort(listOfPoints.begin() + 1, listOfPoints.end(), sortByAngel);
    
            vector<Point> pointsNoDuplicatedAngle = removeDuplicatePointWithSameAngle(listOfPoints);
            if (pointsNoDuplicatedAngle.size() < 3) {
                noEnoughPoints(fin, fout, pointsNoDuplicatedAngle, index, numOfPoints);
                continue;
            }
            
            stack<Point> result_stack;
            result_stack.push(pointsNoDuplicatedAngle[0]);
            result_stack.push(pointsNoDuplicatedAngle[1]);
            result_stack.push(pointsNoDuplicatedAngle[2]);
            
            calculatintConvexHull(pointsNoDuplicatedAngle, result_stack);
            
            vector<Point> result(result_stack.size());
            for (int i = 0; i < result.size(); ++i) {
                result[i] = result_stack.top();
                result_stack.pop();
            }
            
            std::sort(result.begin(), result.end());
            origin = *(result.begin());
            std::sort(result.begin() + 1, result.end(), sortByAngel);
            std::reverse(result.begin() + 1, result.end());
            
            printListOfPoints(result, index, fout);
            printListOfPoints(result, index, cout);
            fin >> numOfPoints;
            index++;
        }
    }
}
