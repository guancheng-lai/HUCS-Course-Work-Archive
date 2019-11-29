//
//  Map.hpp
//  345 Project Map Part 1
//
//  Created by Guancheng Lai on 3/2/18.
//  Copyright � 2018 Guancheng Lai. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace util
{
    template <typename KeyType, typename ValueType>
    class Map
    {
    public:
        class Wrapper
        {
        public:
            operator ValueType&();                                  //typecast operator
            ValueType* operator &();                                //Address operator
            const ValueType& operator =(const ValueType& rValue);   //
            
        private:
            Wrapper(Map &map, const KeyType &key);
            Wrapper(const Wrapper & value);
            Map& map;
            KeyType key;
            ValueType* value;
            
            friend class Map;
        };
        
        class Iterator
        {
        public:
            void operator++();
            void operator--();
            void operator++(int junk);
            void operator--(int junk);
            ValueType& operator*();
            
        private:
            Iterator(Map& map, int index);
            
            Map& map;
            int index;
            friend class Map;
        };
        
        
        class IVisitor
        {
        public:
            virtual void visit(KeyType& , ValueType&);
        };
        
        Iterator getIterator(KeyType &);
        Wrapper operator[](const KeyType& key);
        unsigned size();
        void visit(IVisitor &);
        
    private:
        std::vector<KeyType> keys;
        std::vector<ValueType> values;
        
        ValueType* find(const KeyType &key);
        ValueType* set(const KeyType &key, const ValueType &value);

    };
    
    
    
    /*==========================================================================
     * Map class methods
     */
    
    template <typename KeyType, typename ValueType>
    typename Map<KeyType, ValueType>::Wrapper Map<KeyType, ValueType>::operator[](const KeyType& key)
    {
        Wrapper result(*this, key);
        return result;
    }
    
    template <typename KeyType, typename ValueType>
    unsigned Map<KeyType, ValueType>::size()
    {
        return keys.size();
    }
    
    template <typename KeyType, typename ValueType>
    ValueType* Map<KeyType, ValueType>::find(const KeyType &key)
    {
        ValueType* result = NULL;
        for (int i = 0; i < keys.size(); i++)
        {
            if (key == keys[i])
            {
                result = &(values[i]);
            }
        }
        return result;
    }
    
    template <typename KeyType, typename ValueType>
    ValueType* Map<KeyType, ValueType>::set(const KeyType &key, const ValueType &value)
    {
        ValueType* result = find(key);
        if (result != NULL)
        {
            *result = value;
        }
        else
        {
            keys.push_back(key);
            values.push_back(value);
            result = find(key);
        }
        return result;
    }
    
    template <typename KeyType, typename ValueType>
    typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::getIterator(KeyType& key)
    {
        if(find(key) == NULL)
        {
            throw std::range_error("Key no found in the map");
        }
        else
        {
            int position = int(std::find(keys.begin(), keys.end(), key) - keys.begin());
            Iterator result(*this, position);
            return result;
        }
    }
    
    template <typename KeyType, typename ValueType>
    void Map<KeyType, ValueType>::visit(IVisitor& iv)
    {
        for(int i = 0; i < values.size();i++)
        {
            iv.visit(keys[i], values[i]);
        }
    }
    
    /*==========================================================================
     * Wrapper methods
     */
    
    template <typename KeyType, typename ValueType>
    Map<KeyType, ValueType>::Wrapper::Wrapper(Map &map, const KeyType &key) :
    map(map), key(key)
    {
        value = map.find(key);
    }
    
    //Copy constructor
    template <typename KeyType, typename ValueType>
    Map<KeyType, ValueType>::Wrapper::Wrapper(const Wrapper& rValue) :
    map(rValue.map), key(rValue.key), value(rValue.value)
    {

    }
    
    //conversion operator, from a Wrapper to a ValueType
    template <typename KeyType, typename ValueType>
    Map<KeyType, ValueType>::Wrapper::operator ValueType&()
    {
        if (value == NULL)
        {
            throw std::range_error("Key no found in the map");
        }
        return *value;
    }
    
    //address of operator. This is used when the programmer tries to
    //find the address o f a Wrapper object.  We return the address of the
    //value inside the wrapper instead.
    template <typename KeyType, typename ValueType>
    ValueType* Map<KeyType, ValueType>::Wrapper::operator &()
    {
        if (value == NULL)
        {
            throw std::range_error("Key no found in the map");
        }
        return value;
    }
    
    //assignment operator.  This is used when a wrapper is the l-value in an assignment
    //and the r-value is of type ValueType
    template <typename KeyType, typename ValueType>
    const ValueType& Map<KeyType, ValueType>::Wrapper::operator =(const ValueType& rValue)
    {
        map.set(key, rValue);
        return rValue;
    }
    
    /*==========================================================================
     * iterator methods
     */
    
    template <typename KeyType, typename ValueType>
    Map<KeyType, ValueType>::Iterator::Iterator(Map &map, int index):
    map(map), index(index)
    {

    }
    
    template <typename KeyType, typename ValueType>
    void Map<KeyType, ValueType>::Iterator::operator++()
    {
        index++;
        //return *this;
    }
    
    template <typename KeyType, typename ValueType>
    void Map<KeyType, ValueType>::Iterator::operator--()
    {
        index--;
        //return *this;
    }
    
    template <typename KeyType, typename ValueType>
    void Map<KeyType, ValueType>::Iterator::operator++(int junk)
    {
        index++;
        //return *this;
    }
    
    template <typename KeyType, typename ValueType>
    void Map<KeyType, ValueType>::Iterator::operator--(int junk)
    {
        index--;
        //return *this;
    }
    
    template <typename KeyType, typename ValueType>
    ValueType& Map<KeyType, ValueType>::Iterator::operator*()
    {
        ValueType& result = map.values.at(index);
        return result;
    }
    
    
}
#endif /* Map_hpp */
