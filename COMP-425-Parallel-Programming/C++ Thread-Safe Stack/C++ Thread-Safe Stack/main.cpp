//
//  main.cpp
//  C++ Thread-Safe Stack
//
//  Created by Guancheng Lai on 11/4/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <thread>
#include <mutex>
#include <shared_mutex>

using namespace std;

template <typename T>
class thread_safe_stack {
    stack<T> safeMemory;
    shared_timed_mutex memoryMutex;
    
public:
    thread_safe_stack() = default;
    
    thread_safe_stack(thread_safe_stack &other) {
        shared_lock<shared_timed_mutex> lock(other.memoryMutex);
        safeMemory = other.safeMemory;
    }
    
    thread_safe_stack(thread_safe_stack &&other) {
        unique_lock<shared_timed_mutex> lock(other.memoryMutex);
        safeMemory = move(other.safeMemory);
    }
    
    thread_safe_stack& operator= (const thread_safe_stack &other) {
        unique_lock<mutex> myLock(memoryMutex, defer_lock);
        shared_lock<shared_timed_mutex> otherLock(other.memoryMutex, defer_lock);
        lock(myLock, otherLock);
        safeMemory = other.safeMemory;
    }
    
    thread_safe_stack& operator= (const thread_safe_stack &&other) {
        unique_lock<mutex> myLock(memoryMutex, defer_lock);
        unique_lock<mutex> otherLock(other.memoryMutex, defer_lock);
        lock(myLock, otherLock);
        safeMemory = other.safeMemory;
    }
    
    void push(T value) {
        shared_lock<shared_timed_mutex> lock(memoryMutex);
        lock(<#_L0 &__l0#>, <#_L1 &__l1#>)
        safeMemory.push(value);
        memoryMutex.unlock();
    }
    
    void pop() {
        lock_guard<shared_timed_mutex> lock(memoryMutex);
        safeMemory.pop();
        
    }
    
    T top() {
        lock_guard<shared_timed_mutex> lock(memoryMutex);
        return safeMemory.top();
    }
    
    size_t size() {
        lock_guard<shared_timed_mutex> lock(memoryMutex);
        return safeMemory.size();
    }
    
};

void push_to_thread_safe_stack (thread_safe_stack<int> &s)
{
    for (int i = 0; i < 1000000; ++i) {
        s.push(1);
    }
}


int main(int argc, const char * argv[])
{
    thread_safe_stack<int> safeStack;
    vector<thread> ts(7);
    for (int i = 0; i < 7; ++i) {
        thread t(push_to_thread_safe_stack, std::ref(safeStack));
        ts[i] = move(t);
    }
    
    
    for (auto & t : ts) {
        t.join();
    }
    
    //thread_safe_stack<int> safeStack2 = safeStack;
    //thread_safe_stack<int> safeStack3(safeStack);
    
    cout << safeStack.size() << " : should be 7000000. "<< endl;
    //cout << safeStack2.size() << " : should be 7000000. "<< endl;
    //cout << safeStack3.size() << " : should be 7000000. "<< endl;
    return 0;
}
