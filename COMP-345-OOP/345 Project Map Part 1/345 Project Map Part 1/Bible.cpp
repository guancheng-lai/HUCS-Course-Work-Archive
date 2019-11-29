//
//  Bible.cpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/13/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Bible.hpp"

Bible* Bible::ptrBible = NULL;

Bible& Bible::getInstance()
{
    if(ptrBible == NULL)
    {
        ptrBible = new Bible();
    }
    return *ptrBible;
}

Bible::Bible():util::Map<VerseKey, Verse>()
{
    readTextFile();
}

Bible::~Bible()
{
    
}

void Bible::readTextFile()
{
    std::ifstream fin("bible.txt");
    std::string current_book_name = "";
    float progress = 0;
    
    while(!fin.eof() && !fin.fail())
    {
        std::string line;
        getline(fin, line);
        if(line.substr(0, 4) == "Book")
        {
            progress = progress + 1.515151515;
            cout << progress << "%\n";
            current_book_name = line.substr(8);
        }
        else
        {
            int chapterNumber;
            int verseNumber;
            std::string verseText;
            std::istringstream sin(line);
            
            sin >> chapterNumber >> verseNumber;
            getline(sin, verseText);
            
            VerseKey vk(current_book_name, chapterNumber, verseNumber);
            Verse v(vk, verseText);
            (*this)[vk] = v;
        }
    }
    cout << "Successful read bible!" << endl;
    fin.close();
}

