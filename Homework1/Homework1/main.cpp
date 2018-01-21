//
//  main.cpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/18/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main(int argc, const char * argv[]) {
    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v;
    string k1;
    assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,v)  &&  k2 == k1);
}
