//
//  VerseKey.cpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/13/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "VerseKey.hpp"

VerseKey::VerseKey()
{
    book = "";
    chapterNumber = 0;
    verseNumber = 0;
}

VerseKey::VerseKey(std::string nameOfBook, int chapNum, int verseNum)
{
    book = nameOfBook;
    chapterNumber = chapNum;
    verseNumber = verseNum;
}

VerseKey::~VerseKey()
{

}

std::string VerseKey::getBookName() const
{
    return book;
}

int VerseKey::getChapterNumber() const
{
    return chapterNumber;
}

int VerseKey::getVerseNumber() const
{
    return verseNumber;
}

VerseKey& VerseKey::operator=(const VerseKey & rightValue)
{
    book = rightValue.book;
    chapterNumber = rightValue.chapterNumber;
    verseNumber = rightValue.verseNumber;
    
    return *this;
}

bool operator==(const VerseKey & leftValue, const VerseKey & rightValue)
{
    bool result = false;
    if(leftValue.getBookName() == rightValue.getBookName()&&
    leftValue.getChapterNumber() == rightValue.getChapterNumber()&&
    leftValue.getVerseNumber() == rightValue.getVerseNumber())
    {
        result = true;
    }
    
    return result;
}

std::istream& operator>>(std::istream& VK_input, VerseKey & rightValue)
{
    std::string book;
    int chapterNumber;
    int verseNumber;
    
    cout << "Book?";
    VK_input >> book;
    
    cout << "Chapter?";
    VK_input >> chapterNumber;
    
    cout << "Verse?";
    VK_input >> verseNumber;
    
    return VK_input;
}
