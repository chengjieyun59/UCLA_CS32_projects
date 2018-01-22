//
//  newMap.hpp
//  Homework1 #5 newMap
//
//  Created by Jie-Yun Cheng on 1/21/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#ifndef NEWMAP_INCLUDED
#define NEWMAP_INCLUDED

#include <cstdlib>
#include <string>

using KeyType = std::string;
using ValueType = double; // type alias: a name that is a synonym for some type
const int DEFAULT_MAX_ITEMS = 250;

class Map
{
public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    Map(int max_size); // added another constructor
    ~Map(); // added a destructor
    
    Map(const Map &old); // copy constructor
    Map &operator=(const Map &src); // assignment operator
    
    bool empty() const;  // Return true if the map is empty, otherwise false.
    
    int size() const;    // Return the number of key/value pairs in the map.
    
    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    
    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
    
    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    
    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    
    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    
    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)
    
    void swap(Map& other);
    // Exchange the contents of this map with the other one.
    
private:
    int m_size;
    
    struct AllData {
        KeyType m_key;
        ValueType m_value;
    }; // you may declare private structs inside the Map class
    // two public data members in the helper structure in the private section of Map
    
    // AllData m_data[DEFAULT_MAX_ITEMS];
    AllData* m_data;
};

#endif // NEWMAP_INCLUDED

