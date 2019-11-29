//
//  Bible.hpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/13/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#ifndef Bible_hpp
#define Bible_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Map.hpp"
#include "Verse.hpp"
#include "VerseKey.hpp"

class Bible : public util::Map<VerseKey, Verse>
{
public:
    ~Bible();
    static Bible& getInstance();
    
private:
    Bible();
    static Bible* ptrBible;
    void readTextFile();
};

#endif /* Bible_hpp */
