//
//  main.cpp
//  Homework4
//
//  Created by Jie-Yun Cheng on 3/5/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// for question 1- made by the professor
void test()
{
    Map<int, double> mid;
    Map<string, int> msi;
    assert(msi.empty());
    assert(msi.size() == 0);
    assert(msi.insert("Hello", 10));
    assert(mid.insert(10, 3.5));
    assert(msi.update("Hello", 20));
    assert(mid.update(10, 4.75));
    assert(msi.insertOrUpdate("Goodbye", 30));
    assert(msi.erase("Goodbye"));
    assert(mid.contains(10));
    int k;
    assert(msi.get("Hello", k));
    string s;
    assert(msi.get(0, s, k));
    Map<string, int> msi2(msi);
    msi2.swap(msi);
    msi2 = msi;
    combine(msi,msi2,msi);
    combine(mid,mid,mid);
    subtract(msi,msi2,msi);
    subtract(mid,mid,mid);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

/*
// for question 1- made by self
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

/*
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
*/
