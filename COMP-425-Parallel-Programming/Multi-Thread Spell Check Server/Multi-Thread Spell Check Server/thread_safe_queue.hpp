//
//  thread_safe_queue.hpp
//  Multi-Thread Spell Check Server
//
//  Created by Guancheng Lai on 12/20/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef thread_safe_queue_hpp
#define thread_safe_queue_hpp

#include <stdio.h>
#include "request.hpp"
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

std::shared_timed_mutex m;

template <typename T>
class safe_queue
{
private:
    std::queue<http::server::request> threadPool;
    
public:
    void enqueue(T t);
    T dequeue();
};

template <typename T>
void safe_queue<T>::enqueue(T request)
{
    m.lock();
    threadPool.push(request);
    m.unlock();
}

template <typename T>
T safe_queue<T>::dequeue()
{
    T result = nullptr;
    m.lock();
    
    if (!threadPool.empty())
    {
        result = threadPool.front();
        threadPool.pop();
    }
    
    m.unlock();
    
    return result;
}

#endif /* thread_safe_queue_hpp */
