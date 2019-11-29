//
//  printWords.cpp
//  C++ thread_demo
//
//  Created by Guancheng Lai on 10/27/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
using std::thread;
using std::cout;
using std::endl;
using std::cin;

void printWords()
{
    
    
    cout << "A" << endl;
}

int main(int argc, char * argv[])
{
    thread printer_a {printWords};
    printer_a.join();
    
}
