//
//  VerseKey.hpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/13/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef VerseKey_hpp
#define VerseKey_hpp

#include <stdio.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

class VerseKey
{
public:
    VerseKey(std::string, int ,int);
    VerseKey();
    ~VerseKey();
    VerseKey& operator =(const VerseKey &);
    
    std::string getBookName() const;
    int getChapterNumber() const;
    int getVerseNumber() const;
    
private:
    std::string book;
    int chapterNumber;
    int verseNumber;
    
    
};

bool operator ==(const VerseKey &, const VerseKey &);
std::istream& operator>>(std::istream &, VerseKey &);

#endif /* VerseKey_hpp */
