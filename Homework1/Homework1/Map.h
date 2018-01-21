//
//  Map.hpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/18/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <iostream>
using namespace std;

class Map
{
public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    
    bool empty();  // Return true if the map is empty, otherwise false.
    int size();    // Return the number of key/value pairs in the map.
    
    bool insert(const std::string& key, const double& value);
    bool update(const std::string& key, const double& value);
    bool insertOrUpdate(const std::string& key, const double& value);
    bool erase(const std::string& key);
    bool contains(const std::string& key);
    bool get(const std::string& key, double& value);
    bool get(int i, std::string& key, double& value);
    void swap(Map& other);
    
private:
    int m_size;
    
};

#endif // MAP_INCLUDED
