//
//  History.cpp
//  Project1
//
//  Created by Jie-Yun Cheng on 1/12/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "History.h"

History::History(int nRows, int nCols)
: m_row(nRows), m_col(nCols)
{
    
} // The constructor initializes a History object that corresponds to a City with nRows rows and nCols columns. You may assume (i.e., you do not have to check) that it will be called with a first argument that does not exceed MAXROWS and a second that does not exceed MAXCOLS, and that neither argument will be less than 1.

bool History::record(int r, int c){
    if (r<0 || r>MAXROWS || c<0 || c>MAXCOLS)
        return false;
    /*if (Flatulan.possiblyGetConverted() == true)
    {
        
    }*/
    
    return true;
} // The record function is to be called to notify the History object that a Flatulan was preached to but was not converted at a grid point. The function returns false if row r, column c is not within the City; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the City (e.g., row 1, column 1 is the upper-left-most position).

void History::display() const{
    
} // The display function clears the screen and displays the history grid as the posted programs do. This function does clear the screen, display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue. after the display. (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
