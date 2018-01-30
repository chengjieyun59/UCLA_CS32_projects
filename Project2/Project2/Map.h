//
//  Map.hpp
//  Project2
//
//  Created by Jie-Yun Cheng on 1/27/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <cstdlib>
#include <string>
//#include "IntWrapper.h"       // TODO: remove this line after testing

using KeyType = std::string;
using ValueType = double;
//using ValueType = IntWrapper; // TODO: replace this line after testing

class Map
{
public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    ~Map(); // added a destructor
    
    Map(const Map& old); // copy constructor
    Map& operator=(const Map& src); // assignment operator

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
    
    // nodes don't need to be in any order later
    // make a circular doubly linked list
    struct Node {
        KeyType m_key;
        ValueType m_value;
        Node* next;
        Node* prev;
    };
    
    Node* head; // points to a dummy node
    // head->next points to first element and head->prev points to last element
};

// two non-member functions
bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result); // Should I include this here?

// inline functions
inline
int Map::size() const{
    return m_size;
}

inline
bool Map::empty() const{
    return (size()==0);
}

#endif // MAP_INCLUDED
