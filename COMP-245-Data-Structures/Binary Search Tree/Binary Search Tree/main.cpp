//
//  main.cpp
//  Binary Search Tree
//
//  Created by Guancheng Lai on 12/6/17.
//  Copyright © 2017 Guancheng Lai. All rights reserved.
//

/*This is a program to test basic BST functionality*/

#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"
using namespace std;

int main(void)
{
    ifstream fin;
    string filename, word;
    BST wordList;
    
    cout << "name of input file: ";
    getline(cin, filename);
    fin.open(filename);
    if (fin.fail())
    {
        cout << "invalid filename...program exiting" << endl;
        exit(1);
    }
    
    //build the BST from the input text file
    while (fin >> word)
    {
        if (wordList.Insert(word))
        {
            cout << word << " inserted into binary search tree " << endl;
        }
        else
        {
            cout << "not enough heap space to finish program...exiting" << endl;
            exit(2);
        }
    }
    
    //initial word list
    cout << "List of words stored in alphabetical order..." << endl;
    wordList.Print();
    cout << endl << endl;
    
    //deletion of words
    string wordToDelete;
    cout << "word to delete from list <enter EXIT to finish> ";
    cin >> wordToDelete;
    while (wordToDelete != "EXIT")
    {
        if (wordList.Delete(wordToDelete))
        {
            cout << wordToDelete << " deleted" << endl;
        }
        else
        {
            cout << wordToDelete << " not found" << endl;
        }
        cout << "word to delete from list <enter EXIT to finish> ";
        cin >> wordToDelete;
    }
    
    //Final word list
    cout << "Final list of words..." << endl;
    wordList.Print();
    
    fin.close();
    
}


