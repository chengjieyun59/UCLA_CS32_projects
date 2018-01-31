//
//  Map.cpp
//  Project2
//
//  Created by Jie-Yun Cheng on 1/27/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"

Map::Map()
:m_size(0){
    head = new Node; // dummy node
    head -> prev = head;
    head -> next = head; // When both the previous and next points to m_head itself,
                             // it means the list is empty
} // Create an empty map

Map::~Map()
{
    Node* p = head -> prev; // to delete the dummy node too
    while(m_size >= 0)
    {
        Node* temp = p;
        p = p -> prev;
        delete temp;
        m_size--; //will this end at 0 or -1?
    }
} // destructor
// When a Map is destroyed, the nodes in the linked list must be deallocated.

Map::Map(const Map& src)
: m_size(src.m_size){
    head = new Node; // dummy node
    Node *temp = head;
    Node *temp_src = src.head; // use temp_src, so won't accidentally modify src
    
    while (temp_src->next != src.head) // if hasn't looped through the whole list
    {
        // enough new nodes must be allocated to hold a duplicate of the original list
        Node *newNode = new Node;
        
        // copy temp_src into newNode
        newNode -> m_key = temp_src -> m_key;
        newNode -> m_value = temp_src -> m_value;
        
        // doubly linked
        newNode -> prev = temp;
        temp -> next = newNode;
        temp = newNode; // assign
        temp_src = temp_src -> next; // iterate
    }
    // make circular
    head -> prev = temp;
    temp -> next = head;
} // copy constructor
// When a brand new Map is created as a copy of an existing Map, enough new nodes must be allocated to hold a duplicate of the original list.

Map& Map::operator=(const Map& src)
{
    // need to make sure that left hand side and right hand side aren't already the same
    if (this != &src)
    {
        Map temp(src); // temp holds the right hand side
        swap(temp); // now left hand side holds temp
    } // temp is gone now
    return (*this);
}// assignment operator
// When an existing Map (the left-hand side) is assigned the value of another Map (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).

bool Map::insert(const KeyType& key, const ValueType& value){
    if (! contains(key)){
        Node* p = head -> next;
        p = new Node;
        p -> m_key = key;
        p -> m_value = value;

        // put p after head
        p -> prev = head;
        p -> next = head -> next;
        head -> next = p;
        p -> next -> prev = p;
        
        m_size = m_size + 1;
        return true;
    }
    return false;
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).

bool Map::update(const KeyType& key, const ValueType& value){
    for (Node* p = head -> next; p!= head; p = p-> next)
    {
        if (key == p -> m_key){
            p -> m_value = value;
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
    if (! contains(key)){
        insert(key, value);
        return true;
    }
    update(key, value);
    return true;
}
// Notice that there is now no a priori limit on the maximum number of key/value pairs in the Map (so insertOrUpdate should always return true).
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.

// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.

// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).

bool Map::erase(const KeyType& key){
    Node* p = head -> next;
    
    // loop through the whole list until it's empty or finds the key
    while (p != head && p -> m_key != key)
    {
        p = p -> next;
    }
    
    if (p == head)
        return false; // exhausted list and couldn't find the key
    else {
        p -> prev -> next = p -> next; // assign p -> next to its previous node's next pointer
        p -> next -> prev = p -> prev; // assign p -> prev to its next node's previous pointer
        delete p; // destruct
        m_size = m_size - 1;
    }
    return true;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const{
    // loop through the whole list
    for (Node* p = head -> next; p!= head; p = p-> next)
        if (key == p -> m_key)
            return true;
    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const{
    for (Node* p = head -> next; p!= head; p = p-> next)
    {
        if (key == p -> m_key){
            value = p -> m_value;
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
    if (i < 0 || i > size())
        return false;
    // Notice also that, as in Homework 1, if a Map has a size of n, then the values of the first parameter to the three-parameter form of get for which that function retrieves a key and a value and returns true are 0, 1, 2, ..., n-1; for other values, it returns false without setting its second and third parameters. This is the same visible behavior as in Homework 1.
    
    Node* p = head;
    while (i >= 0)
    {
        p = p-> next;
        i--;
    }
    key = p -> m_key;
    value = p -> m_value;
    return true;
    // Another requirement is that as in Problem 5 of Homework 1, the number of statement executions when swapping two maps must be the same no matter how many key/value pairs are in the maps.
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

void Map::swap(Map& other){
    Node* temp;
    int temp_size;
    
    temp = head;
    temp_size = size();
    
    head = other.head;
    m_size = other.m_size;
    
    other.head = temp;
    other.m_size = temp_size;
}
// Exchange the contents of this map with the other one.

// Non-member functions
// Notice that combine & subtract are non-member functions: They are not members of Map or any other class, so they must not access private members of Map. Be sure these functions behave correctly in the face of aliasing: What if m1 and result refer to the same Map, for example?
bool combine(const Map& m1, const Map& m2, Map& result){
    // only the 3-parameter get function can loop through each index without needing head, prev, or next
    Map temp_result;
    KeyType key;
    ValueType value1;
    ValueType value2;
    bool return_bool;
    return_bool = true; // 4.2
    
    for (int i = 0; i < m1.size(); i++)
    {
        m1.get(i, key, value1);
        if (m2.get(key, value2) == true && value1 == value2)
            temp_result.insert(key, value1); // 2
        else if (m2.contains(key) == false)
            temp_result.insert(key, value1); // 1.1
        else if (m2.get(key, value2) == true && value1 != value2)
            return_bool = false; // return later // 4.1
    }
    
    for (int i = 0; i < m2.size(); i++)
    {
        m2.get(i, key, value2);
        if (m1.get(key, value1) == true)
            break; // already added into temp_result
        else if (m1.contains(key) == false)
            temp_result.insert(key, value2); // 1.2.
    }
    
    result.swap(temp_result);
    return return_bool;
}
/*
When this function returns, result must consist of pairs determined by these rules:
1.1. If a key appears only in m1, then result must contain a pair consisting of that key and its corresponding value.
1.2. If a key appears only in m2, then result must contain a pair consisting of that key and its corresponding value.
2. If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain exactly one pair with that key and value.
3. When this function returns, result must contain no pairs other than those required by these rules. (You must not assume result is empty when it is passed in to this function; it might not be.)
4.1. If there exists a key that appears in both m1 and m2, but with different corresponding values, then this function returns false;
4.2. if there is no key like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
*/

void subtract(const Map& m1, const Map& m2, Map& result){
    
    
    
    
    
    return;
} // TODO
/*
 When this function returns, result must contain one copy of all the pairs in m1 whose keys don't appear in m2; it must not contain any other pairs. (You must not assume result is empty when it is passed in to this function; it may not be.)
 
 For example, if m1 consists of the three pairs (in any order)
 
 "Fred"  123      "Ethel"  456      "Lucy"  789
 and m2 consists of (in any order)
 
 "Lucy"  789      "Ricky"  321      "Ethel"  654
 then no matter what value it had before, result must end up as a map consisting of
 
 "Fred"  123
*/
