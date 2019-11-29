//
//  Verse.cpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/13/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include "Verse.hpp"
Verse::Verse(VerseKey vk, std::string text)
{
    verseKey = vk;
    verseText = text;
}

std::string Verse::getVerse() const
{
    return verseText;
}

std::ostream& operator<<(std::ostream& out, Verse& rValue)
{
    out << rValue.getVerse();
    return out;
}
