//
//  thread_safe_map.hpp
//  Multi-Thread Spell Check Server
//
//  Created by Guancheng Lai on 4/23/19.
//  Copyright © 2019 Guancheng Lai. All rights reserved.
//

#ifndef thread_safe_map_hpp
#define thread_safe_map_hpp

#include <stdio.h>
#include <string>
#include <map>

template <typename T>
class thread_safe_map
{
private:
    std::map<std::string, T> cacheMap;
public:
    <#member functions#>
};

#endif /* thread_safe_map_hpp */
