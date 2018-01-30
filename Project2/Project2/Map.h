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
    Map(const Map& src); // copy constructor
    Map& operator=(const Map& src); // assignment operator

    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    
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
