//
//  CarMap.cpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/21/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

#include "CarMap.h"
#include "Map.h"

CarMap::CarMap(){
} // Create an empty car map.

// The code actually executes in an if statement condition
// so I can actually delete the current if conditions and just put in the insert function in the if condition, and insert will execute
bool CarMap::addCar(KeyType license){
    if (!m_carmap.contains(license) && m_carmap.size() < DEFAULT_MAX_ITEMS){
        m_carmap.insert(license, 0);
        return true;
    }
    return false;
}
// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry f o r that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.

double CarMap::gas(KeyType license) const{
    ValueType gallons;
    if (m_carmap.contains(license)){
        m_carmap.get(license, gallons);
        return gallons;
    }
    return -1;
}
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.

bool CarMap::addGas(KeyType license, ValueType gallons){
    if (!m_carmap.contains(license) || gallons < 0)
        return false;
    m_carmap.update(license, gas(license) + gallons);
    return true;
}
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.

bool CarMap::useGas(KeyType license, ValueType gallons){
    if (!m_carmap.contains(license) || gallons < 0 || gallons > gas(license))
        return false;
    m_carmap.update(license, gas(license) - gallons);
    return true;
}
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.

int CarMap::fleetSize() const{
    return m_carmap.size();
} // Return the number of cars in the CarMap.

void CarMap::print() const{
    KeyType license;
    ValueType gallons;
    
    for (int i = 0; i < m_carmap.size(); i++){
        m_carmap.get(i, license, gallons);
        cout << license << " " << gallons << endl;
    }
}
// Write to cout one line f o r every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
