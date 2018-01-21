//
//  main.cpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/18/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"
#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(){
    // test cases
    CarMap cm;  // maps strings to doubles
    assert(cm.fleetSize() == 0);
    ValueType gas = 50;
    assert(cm.addCar("AAA") == true);
    assert(cm.addGas("AAA", gas) == true);
    assert(cm.addGas("AAB", gas) == false);
    assert(cm.fleetSize() == 1);
    
    assert(cm.gas("AAA") == 50);
    assert(cm.useGas("AAB", 3) == false);
    assert(cm.useGas("AAA", 23) == true);
    assert(cm.gas("AAA") == 27);
    assert(cm.addCar("BBB") == true);
    
    cm.print();
    cout << "Passed all tests" << endl;
}

/*
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    // tc31
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
    cout << "Passed all tests" << endl;
}*/
