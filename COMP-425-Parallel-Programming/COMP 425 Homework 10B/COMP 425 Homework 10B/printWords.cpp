//
//  COMP 425 Homework 10.2
//  printWords.cpp
//  C++ thread homework
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

bool stop = false;

void printWords(char wordToPrint)
{
    if (wordToPrint == 'A') {
        while (!stop) {
            cout << "A" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if (wordToPrint == 'B') {
        while (!stop) {
            cout << "B" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    else {
        int counter(0);
        while (!stop) {
            cout << "C" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            
            counter++;
            if (counter == 4) {
                stop = true;
            }
            
        }
    }
}

int main(int argc, char * argv[])
{
    thread thread_print_a_every_oneSecond (printWords, 'A');
    thread thread_print_b_every_twoSecond (printWords, 'B');
    thread thread_print_c_every_fiveSecond (printWords, 'C');
    
    thread_print_a_every_oneSecond.join();
    thread_print_b_every_twoSecond.join();
    thread_print_c_every_fiveSecond.join();
}
