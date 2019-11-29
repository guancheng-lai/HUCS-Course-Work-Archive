//
//  
//  COMP 425 Homework #11
//
//  Created by Guancheng Lai on 10/31/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <thread>
#include <numeric>
#include <vector>
#include <chrono>
#include <iterator>
using std::thread;
using std::cout;
using std::endl;
using std::vector;
using std::iterator;

template <typename Iterator, typename Number>
void addUp(Iterator begin, Iterator end, Number& result)
{
    result = std::accumulate(begin, end, Number{});
}
//void addUp(vector<int>::iterator begin, vector<int>::iterator end, int &result)
//{
//    result = std::accumulate(begin, end, 0);
//}

template <typename Iterator, typename Number>
thread createThread(Iterator begin, Iterator end, Number& result)
{
    return thread(addUp, begin end, std::ref(result));
}
//thread createThread(vector<int>::iterator begin, vector<int>::iterator end, int &result)
//{
//    return thread(addUp, begin, end, std::ref(result));
//}

template <typename Iterator, typename Number>
int propagate(Iterator begin, Iterator end)
{
    // Check corner case
    if (std::distance(begin, end) <= 0) {
        return 0;
    }
    else if (std::distance(begin, end) == 1) {
        return *begin;
    }
    
    // Assign thread number
    int numOfThreads;
    if (thread::hardware_concurrency() > 0) {
        numOfThreads = std::distance(begin, end) < thread::hardware_concurrency() ? int(std::distance(begin, end)) : thread::hardware_concurrency();
    }
    else {
        numOfThreads = 2;
    }
    
    // Initiallize necessary variable
    int subrangePerThread = int(std::distance(begin, end) / numOfThreads);
    vector<int> sum(numOfThreads);
    vector<int>::iterator begin_iterator = begin;
    vector<int>::iterator end_iterator = begin; std::advance(end_iterator, subrangePerThread);
    
    // Propagate threads and undate iterator
    vector<thread> threads(numOfThreads - 1);
    for (int i = 0; i < numOfThreads - 1; ++i) {
        threads[i] = createThread(begin_iterator, end_iterator, sum[i]);
        begin_iterator = end_iterator;
        std::advance(end_iterator, subrangePerThread);
    }
    
    // Calculate the rest in main thread
    sum[numOfThreads - 1] = std::accumulate(begin_iterator, end, 0);
    
    for (int i = 0; i < numOfThreads - 1; ++i) {
        threads[i].join();
    }
    
    return std::accumulate(sum.begin(), sum.end(), 0);
}
//int propagate(vector<int>::iterator begin, vector<int>::iterator end)
//{
//    // Check corner case
//    if (std::distance(begin, end) <= 0) {
//        return 0;
//    }
//    else if (std::distance(begin, end) == 1) {
//        return *begin;
//    }
//
//    // Assign thread number
//    int numOfThreads;
//    if (thread::hardware_concurrency() > 0) {
//        numOfThreads = std::distance(begin, end) < thread::hardware_concurrency() ? int(std::distance(begin, end)) : thread::hardware_concurrency();
//    }
//    else {
//        numOfThreads = 2;
//    }
//
//    // Initiallize necessary variable
//    int subrangePerThread = int(std::distance(begin, end) / numOfThreads);
//    vector<int> sum(numOfThreads);
//    vector<int>::iterator begin_iterator = begin;
//    vector<int>::iterator end_iterator = begin; std::advance(end_iterator, subrangePerThread);
//
//    // Propagate threads and undate iterator
//    vector<thread> threads(numOfThreads - 1);
//    for (int i = 0; i < numOfThreads - 1; ++i) {
//        threads[i] = createThread(begin_iterator, end_iterator, sum[i]);
//        begin_iterator = end_iterator;
//        std::advance(end_iterator, subrangePerThread);
//    }
//
//    // Calculate the rest in main thread
//    sum[numOfThreads - 1] = std::accumulate(begin_iterator, end, 0);
//
//    for (int i = 0; i < numOfThreads - 1; ++i) {
//        threads[i].join();
//    }
//
//    return std::accumulate(sum.begin(), sum.end(), 0);
//}

int main(int argc, const char * argv[])
{
    cout << "How many 1s you want to add-up?\nThis program will construct a vector which all the values are 1, the length of the vector is the value you input.\nThe result should equal exactly what you input here." << endl;
    int nValues;
    std::cin >> nValues;
    vector<int> ints(nValues, 1);
    
    auto start = std::chrono::high_resolution_clock::now();
    //int parallel_result = propagate(ints.begin(), ints.end());
    int parallel_result = propagate<vector<int>::iterator, int>(ints.begin(), ints.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto parallelTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int sequencial_result = 0;
    for (int i = 0; i < nValues; ++i) {
        sequencial_result += ints[i];
    }
    end = std::chrono::high_resolution_clock::now();
    auto seqTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    

    cout << endl;
    cout << "Parallel Result   = " << parallel_result << " in " << parallelTime.count()  << "ns" << endl;
    cout << "Sequencial Result = " << sequencial_result << " in " << seqTime.count() << "ns" << endl;
}
