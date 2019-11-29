//
//  main.cpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 2/27/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <string>
#include <exception>
#include "Map.hpp"
#include "VerseKey.hpp"
#include "Verse.hpp"
#include "Bible.hpp"
#include "BibleWordCounter.hpp"
using util::Map;
using std::string;
using std::cout;
using std::cin;
using std::endl;

VerseKey promptInput();
int main(int argc, const char * argv[])
{
    Bible& bible1 = Bible::getInstance();
//    string continueRead;
//
//    do
//    {
//        VerseKey vk1 = promptInput();
//        try{
//            Verse v = bible1[vk1];
//            cout << v << endl;
//        }catch (...){
//            std::cerr << "Verse not found" << endl;
//        }
//
//        cout << "Continue? y/n\n";
//        cin >> continueRead;
//        cin.ignore();
//    }
//    while(continueRead == "Y" || continueRead == "y");
    
    
    VerseKey vk1 = promptInput();
    Map<VerseKey, Verse>::Iterator i = bible1.getIterator(vk1);
    
    cout << endl << "Testing iterator" << endl;
    Verse v = bible1[vk1];
    cout << v << endl;
    cout << *i << endl;
    i++;
    cout << *i << endl;
    i--;
    cout << *i << endl;
    cout << "Finish testing iterator" << endl;

    cout << "testing visitor(Bible word counter)" << endl;
    cout << "What do you want to find in the bible?" << endl;
    std::string textToFind;
    cin.ignore();
    getline(cin, textToFind);
    BibleWordCounter bwc(textToFind);
    bible1.visit(bwc);
    int timesFound = bwc.getTimesFound();
    cout << "Found: " << textToFind << "  in" << timesFound << "verse appeared." << endl;
    return 0;
}

VerseKey promptInput()
{
    string bookName;
    int chapterNumber;
    int verseNumber;
    
    cout << "Book?" << endl;
    getline(cin, bookName);
    
    cout << "Chapter?" << endl;
    cin >> chapterNumber;
    
    cout << "Verse?" << endl;
    cin >> verseNumber;
    
    VerseKey result(bookName, chapterNumber, verseNumber);
    return result;
}
