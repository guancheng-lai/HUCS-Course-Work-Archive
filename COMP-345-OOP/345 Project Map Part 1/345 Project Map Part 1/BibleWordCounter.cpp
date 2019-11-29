//
//  BibleWordCounter.cpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/23/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "BibleWordCounter.hpp"

BibleWordCounter::BibleWordCounter(std::string word):Bible::IVisitor()
{
    wordToCount = word;
    timesFound = 0;
}

void BibleWordCounter::visit(VerseKey& vk, Verse& v)
{
    std::string tempString = v.getVerse();
    if(tempString.find(wordToCount) != NULL)
    {
        timesFound++;
    }
}

int BibleWordCounter::getTimesFound()
{
    return timesFound;
}
