//
//  newMap.cpp
//  Homework1 #5 newMap
//
//  Created by Jie-Yun Cheng on 1/21/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "newMap.h"

/*
Map::Map(const int max_size)
:m_size(0), m_max_size(max_size){
    m_data = new AllData[m_max_size];
} // Create an empty map (i.e., one with no key/value pairs)
*/

Map::Map()
:m_size(0), m_max_size(DEFAULT_MAX_ITEMS){
    m_data = new AllData[m_max_size];
} // Create an empty map (i.e., one with no key/value pairs)

Map::Map(int max_size)
:m_size(0), m_max_size(max_size){
    m_data = new AllData[m_max_size];
} // added another constructor

Map::~Map()
{
    delete [] m_data;
} // added a destructor

Map::Map(const Map& old)
{
    m_size = old.m_size;
    m_max_size = old.m_max_size;
    m_data = new AllData[m_size];
    for (int j = 0; j < m_size; j++)
        m_data[j] = old.m_data[j];
} // copy constructor

Map& Map::operator=(const Map& src)
{
    if (this != &src)
    {
        Map temp(src);
        swap(temp);
        /*
        delete [] m_data;
        m_size = src.m_size;
        m_data = new AllData[m_size];
        for (int j = 0; j < m_size; j++)
            m_data[j] = src.m_data[j];
        */
    }
    return (*this);
}// assignment operator

bool Map::empty() const{
    if (size() == 0)
        return true;
    else
        return false;
} // Return true if the map is empty, otherwise false.

int Map::size() const{
    return m_size;
} // Return the number of key/value pairs in the map.

bool Map::insert(const KeyType& key, const ValueType& value){
    if (! contains(key) && size() < m_max_size){
        m_data[m_size].m_key = key;
        m_data[m_size].m_value = value;
        m_size++;
        return true;
    } // ? why doesn't the original one work ?
    else
        return false;
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).

bool Map::update(const KeyType& key, const ValueType& value){
    for (int i = 0; i < size() && size() > 0; i++)
    {
        if (key == m_data[i].m_key){
            m_data[i].m_value = value;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    for (int i = 0; i < size() && size() > 0; i++)
    {
        if (key == m_data[i].m_key){
            m_data[i].m_value = value;
            return true;
        }
    }
    if (!contains(key) && size() < m_max_size)
        if (! contains(key) && size() < m_max_size){
            insert(key, value);
            return true;
        }
    return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.

// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.

// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).

bool Map::erase(const KeyType& key){
    for (int i = 0; i < size() && size() > 0; i++)
    {
        if (key == m_data[i].m_key){
            //if (size() == 1)
            //m_size = 0; // special case
            for (int j = i; j < size()-1; j++)
            {
                m_data[j].m_key = m_data[j+1].m_key; // move every key to the left after position i
                m_data[j].m_value = m_data[j+1].m_value;
            }
            m_size--;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const{
    for (int i = 0; i < size() && size() > 0; i++)
    {
        if (key == m_data[i].m_key)
        {
            return true;
        }
    }
    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const{
    for (int i = 0; i < size() && size() > 0; i++)
    {
        if (key == m_data[i].m_key){
            value = m_data[i].m_value;
            return true;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if (i >= 0 && i < size())
    {
        key = m_data[i].m_key;
        value = m_data[i].m_value;
        return true;
    }
    return false;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

void Map::swap(Map& other){
    // declare temp
    int temp_size = m_size;
    int temp_max_size = m_max_size;
    AllData* temp_data = m_data;
    
    // input Map b into Map a
    m_size = other.m_size;
    m_max_size = other.m_max_size;
    m_data = other.m_data;
    
    // input temp into Map b
    other.m_size = temp_size;
    other.m_max_size = temp_max_size;
    other.m_data = temp_data;
} //? How to NOT make an extra array temp?
// Exchange the contents of this map with the other one.
