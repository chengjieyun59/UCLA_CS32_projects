//
//  Player.hpp
//  Project1
//
//  Created by Jie-Yun Cheng on 1/12/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED
// #include <stdio.h>

class City;

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_health;
    int   m_age;
};

#endif // PLAYER_INCLUDED
