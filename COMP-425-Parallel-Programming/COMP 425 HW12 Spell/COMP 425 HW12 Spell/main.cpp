//
//  main.cpp
//  COMP 425 HW12 Spell
//
//  Created by Guancheng Lai on 11/7/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <list>
#include <thread>
#include <mutex>
#include <shared_mutex>
using std::cout;
using std::endl;
using std::cin;
using std::set;
using std::string;
using std::mutex;
using std::shared_timed_mutex;
using std::thread;
using std::list;

void join_finished_thread (list<thread> &ts)
{
    for (list<thread>::iterator it = ts.begin(); it != ts.end(); it++) {
        if ((*it).joinable()) {
            (*it).join();
            it = ts.erase(it);
        }
    }
}

void find_word(set<string> &wordSet, string word)
{
    shared_timed_mutex stm;
    std::lock_guard<shared_timed_mutex> lock (stm);
    if (wordSet.count(word) > 0) {
        cout << word << " is correct\n";
    } else if (wordSet.count(word) == 0) {
        cout << word << " is incorrect\n";
    }
}

void add_word(set<string> &wordSet)
{
    shared_timed_mutex stm;
    std::lock_guard<shared_timed_mutex> lock (stm);
    string addWord;
    cin >> addWord;
    wordSet.insert(addWord);
}


void read_in_words (std::ifstream &fin, set<string> &wordSet)
{
    string s;
    fin >> s;
    
    while (fin) {
        wordSet.insert(s);
        fin >> s;
    }
    cout << "Words read in finished\nPlease input command.\n";
    
}

int main(int argc, const char * argv[])
{
    std::ifstream fin(argv[1]);
    
    if (fin.good()) {
        set<string> wordSet;
        read_in_words(fin, wordSet);
        
        string command;
        cin >> command;
        
        list<thread> ts;
        while (cin) {
            if (command == "end") {
                return 0;
            } else if (command == "add") {
                thread t_add(add_word, std::ref(wordSet));
                ts.push_back(std::move(t_add));
            } else {
                thread t_find(find_word, std::ref(wordSet), command);
                ts.push_back(std::move(t_find));
            }
            
            cin >> command;
            join_finished_thread(ts);
        }
    }
    else
    {
        cout << "Word File not found." << endl;
    }
    

}
