//
//  testCarMap.cpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/21/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"
#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

/*
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
    assert(cm.gas("AAA") == 27); // 50 - 23 = 27
    
    assert(cm.addCar("BBB") == true);
    assert(cm.addGas("AAA", 5) == true);
    assert(cm.gas("AAA") == 32); // 27 + 5 = 32
    
    cm.print();
    cout << "Passed all tests" << endl;
}
*/
