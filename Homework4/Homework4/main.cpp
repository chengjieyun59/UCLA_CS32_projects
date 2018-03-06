//
//  main.cpp
//  Homework4
//
//  Created by Jie-Yun Cheng on 3/5/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Map.h"
#include <string>
using std::string;

/*
// for question 1
int main() {
    Map<int, double> a;
    assert(a.insert(42, -1.25));

    Map<string, int> m;
    assert(m.insert("Fred", 2.956));
    assert(m.insert("Ethel", 3.538));
    assert(m.size() == 2);
    
    int v = 42;
    assert(!m.get("Lucy", v));
    assert(m.get("Fred", v)  &&  v == 2);
    
    v = 42;
    string x = "Lucy";
    assert(m.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 2)  ||  (x == "Ethel"  &&  v == 3)));
    
    string x2 = "Ricky";
    assert(m.get(1, x2, v)  &&
           ((x2 == "Fred"  &&  v == 2)  ||  (x2 == "Ethel"  &&  v == 3))  &&
           x != x2);
    
}
*/

// for question 2
class Coord
{
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    Coord() : m_r(0), m_c(0) {}
    double r() const { return m_r; }
    double c() const { return m_c; }
private:
    double m_r;
    double m_c;
};

int main()
{
    Map<int, double> mid;
    mid.insert(42, -1.25);         // OK
    Map<Coord, int> mpi;
    mpi.insert(Coord(40,10), 32);  // error! Why?
}
