//
//  Verse.hpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/13/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Verse_hpp
#define Verse_hpp

#include <stdio.h>
#include <iostream>
#include "VerseKey.hpp"

class Verse
{
public:
    Verse(VerseKey, std::string);
    std::string getVerse() const;
private:
    VerseKey verseKey;
    std::string verseText;
};

std::ostream& operator<<(std::ostream &, Verse &);
#endif /* Verse_hpp */
