//
//  main.cpp
//  C++ condition example
//
//  Created by Guancheng Lai on 11/8/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

queue<int> work_queue;
condition_variable work_queue_condition;
mutex work_queue_mutex;

void getWOrk()
{
    int myData;
    while (cin >> myData) {
        {
            lock_guard<mutex> work_queue_lock(work_queue_mutex);
            work_queue.push(myData);
        }
        work_queue_condition.notify_all();
    }
}

void do_work()
{
    unique_lock<mutex> work_queue_lock(work_queue_mutex);
    work_queue_condition.wait(work_queue_lock, [](){
        return !work_queue.empty();
    });
    
    int myData = work_queue.front();
    work_queue.pop();
    
    myData *= 2;
    cout << myData << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
