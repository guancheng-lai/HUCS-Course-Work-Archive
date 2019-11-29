//
//  BibleWordCounter.hpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/23/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef BibleWordCounter_hpp
#define BibleWordCounter_hpp

#include <stdio.h>
#include <string>
#include "Map.hpp"
#include "Bible.hpp"

class BibleWordCounter : public Bible::IVisitor
{
public:
    BibleWordCounter(std::string word);
    void visit(VerseKey&, Verse&);
    int getTimesFound();
private:
    std::string wordToCount;
    int timesFound;
};
#endif /* BibleWordCounter_hpp */
