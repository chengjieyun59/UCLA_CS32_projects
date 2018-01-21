//
//  CarMap.cpp
//  Homework1
//
//  Created by Jie-Yun Cheng on 1/21/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <cstdlib>
#include <string>

#include "CarMap.h"
#include "Map.h"

CarMap::CarMap()
:m_car(0){
    
} // Create an empty car map.

bool CarMap::addCar(std::string license){
    
    return false;
}
// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.

double CarMap::gas(std::string license) const{
    
    return -1;
}
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.

bool CarMap::addGas(std::string license, double gallons){
    
    return true;
}
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.

bool CarMap::useGas(std::string license, double gallons){
    
    return true;
}
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.

int CarMap::fleetSize() const{
    
    return m_car;
} // Return the number of cars in the CarMap.

void CarMap::print() const{
    
}
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
