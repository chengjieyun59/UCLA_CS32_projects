//
//  main.cpp
//  Project2
//
//  Created by Jie-Yun Cheng on 1/27/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

// tc 02
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    // test empty function
    Map a;
    assert(a.empty());
    
    // test size function
    assert(a.size() == 0);

    // test insert function
    a.insert("A", 10);
    a.insert("B", 44);
    a.insert("C", 10);
    string all;
    double total = 0;
    
    // test get function with 2 parameters
    Map m;  // maps strings to doubles
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
    
    // test get function with 3 parameters
    for (int n = 0; n < a.size(); n++)
    {
        string k;
        double v;
        a.get(n, k, v);
        all += k;
        total += v;
    } // must result in the output being exactly one of the following: ABC64, ACB64, BAC64, BCA64, CAB64, or CBA64
    cout << all << total; // would print CBA64 for my circular doubly linked list
    
    // test swap function
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 1  &&  m2.contains("Fred"));

    // test erase function
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    double va;
    string k1;
    assert(gpas.get(1,k1,va)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,va)  &&  k2 == k1);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
           gpas.contains(""));
    
    // test a combination of functions
    Map m3;
    assert(!m3.erase("Ricky"));
    assert(m3.insert("Fred", 123));
    assert(m3.insert("Ethel", 456));
    assert(m3.size() == 2);
    v = 42;
    assert(!m3.get("Lucy", v)  &&  v == 42);
    assert(m3.get("Fred", v)  &&  v == 123);
    v = 42;
    KeyType x = "Lucy";
    assert(m3.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
    KeyType x2 = "Ricky";
    assert(m3.get(1, x2, v)  && ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  && x != x2);
    
    // test update function
    m3.update("Fred", 999);
    assert(m3.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 999)  ||  (x == "Ethel"  &&  v == 456)));
    
    // test insertOrUpdate function
    m3.insertOrUpdate("Fred", 555);
    assert(m3.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 555)  ||  (x == "Ethel"  &&  v == 456)));
    m3.insertOrUpdate("Mariam", 333);
    assert(m3.get(0, x, v)  &&
           ((x == "Mariam"  &&  v == 333)  ||  (x == "Ethel"  &&  v == 456)));
    
    // test copy constructor
    Map m4 = m3;
    //assert(m4.get(1, x2, v)  && ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  && x != x2);
    
    // test assignment operator
    m2 = m3;
    //assert(m2.get(1, x2, v)  && ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  && x != x2);
}

int main()
{
    test();
    cout << "Passed all tests" << endl; // prints CBA64Passed all tests
}


/*
// tc 03: keytype int, valuetype string
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
 Map m;
 assert(m.insert(10, "diez"));
 assert(m.insert(20, "veinte"));
 assert(m.size() == 2);
 ValueType v = "cuarenta y dos";
 assert(!m.get(30, v)  &&  v == "cuarenta y dos");
 assert(m.get(10, v)  &&  v == "diez");
 v = "cuarenta y dos";
 KeyType x = 30;
 assert(m.get(0, x, v)  &&
 ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
 KeyType x2 = 40;
 assert(m.get(1, x2, v)  &&
 ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
 x != x2);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
*/

/*
 //tc 01
 #include "Map.h"
 #include <type_traits>
 
 #define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }
 
 static_assert(std::is_default_constructible<Map>::value,
 "Map must be default-constructible.");
 static_assert(std::is_copy_constructible<Map>::value,
 "Map must be copy-constructible.");
 
 void ThisFunctionWillNeverBeCalled()
 {
 CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
 CHECKTYPE(&Map::empty,          bool (Map::*)() const);
 CHECKTYPE(&Map::size,           int  (Map::*)() const);
 CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
 CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
 CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
 CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
 CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
 CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
 CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
 CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
 
 CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
 CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
 }
 
 int main()
 {}
 */

/*
//tc00: IntWrapper
#include "Map.h"
#include <iostream>

using namespace std;

void test()
{
    cerr << "test A" << endl;
    Map m;
    cerr << "test B" << endl;
    m.insert("10", IntWrapper(10));
    cerr << "test C" << endl;
    m.insert("20", IntWrapper(20));
    cerr << "test D" << endl;
    Map m2;
    cerr << "test E" << endl;
    m2.insert("30", IntWrapper(30));
    cerr << "test F" << endl;
    m2 = m;
    cerr << "test G" << endl;
    m2.insert("40", IntWrapper(40));
    cerr << "test H" << endl;
}

int main()
{
    test();
    cerr << "DONE" << endl;
}
*/
