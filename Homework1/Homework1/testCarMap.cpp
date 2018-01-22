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

int main(){
    // test cases 1
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
    
    // test cases 2
    CarMap Cars;
    assert(Cars.fleetSize()==0);
    assert(Cars.addCar("cat") && Cars.fleetSize() == 1);
    assert(!Cars.addCar("cat")&& Cars.gas("cat")==0);
    assert(Cars.gas("dog") == -1);
    assert(!Cars.addGas("dog", 2.0));
    assert(!Cars.addGas("cat", -2));
    assert(Cars.addGas("cat", 1) && Cars.gas("cat") == 1);
    assert(Cars.addCar("dog") && Cars.addGas("dog", 5)&& Cars.fleetSize() == 2);
    assert(!Cars.useGas("dog", 6));
    assert(!Cars.useGas("horse", 1));
    assert(!Cars.useGas("dog", -1));
    assert(Cars.useGas("dog", 2) && Cars.gas("dog") == 3);
    Cars.print();
}
