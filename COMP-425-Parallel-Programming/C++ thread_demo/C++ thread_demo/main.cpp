//
//  counting.cpp
//  COMP 425 Homework 10.1
//
//  Created by Guancheng Lai on 10/27/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
using std::thread;
using std::cin;
using std::cout;
using std::endl;

bool stop = false;

void stopTheCounter()
{
    if (cin.ignore()) {
        stop = true;
    }
}

void counting(int &counter)
{
    while (!stop) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << counter << endl;
        counter++;
    }
}

int main(int argc, const char * argv[])
{
    int count(0);
    thread input_thread{ stopTheCounter };
    thread counter_thread{ [&](){ counting(count); } };
    cout << "Start to counting...\n";
    counter_thread.join();
    input_thread.join();
    cout << "Counting finished\n";
}
