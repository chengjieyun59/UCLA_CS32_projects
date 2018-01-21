//
//  Map.cpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/18/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"

Map::Map()
:m_size(0), m_data(){ //? Take away the m_data()?
} // Create an empty map (i.e., one with no key/value pairs)

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
    /* for (int i = 0; i < size(); i++)
    {
        if (key == m_data[i].m_key){
            return false;
        }
    }*/
    // may be able to use contains function?
    if (! contains(key) && size() < DEFAULT_MAX_ITEMS){
        m_size++;
        m_data[m_size-1].m_key = key;
        m_data[m_size-1].m_value = value;
        return true;
    }
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
    if (!contains(key) && size() < DEFAULT_MAX_ITEMS)
        if (! contains(key) && size() < DEFAULT_MAX_ITEMS){
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
    
    Map* otherptr = &other; //otherptr points to Map. This pointer stores the address of other
    KeyType temp_key[DEFAULT_MAX_ITEMS];
    ValueType temp_value[DEFAULT_MAX_ITEMS];
    int temp_size;
    
    //temp = *map1
    temp_size = size();
    for (int i = 0; i < size() && size() > 0; i++)
    {
        temp_key[i] = m_data[i].m_key;
        temp_value[i] = m_data[i].m_value;
    }
    
    //*map1 = *map2
    m_size = otherptr->m_size;
    for (int i = 0; i < size() && size() > 0; i++)
    {
        m_data[i].m_key = otherptr->m_data[i].m_key;
        m_data[i].m_value = otherptr->m_data[i].m_value;
    }
    
    //*other = temp;
    otherptr->m_size = temp_size;
    for (int i = 0; i < size() && size() > 0; i++)
    {
        otherptr->m_data[i].m_key = temp_key[i];
        otherptr->m_data[i].m_value = temp_value[i];
    }
}
// Exchange the contents of this map with the other one.
