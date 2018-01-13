//
//  History.cpp
//  Project1
//
//  Created by Jie-Yun Cheng on 1/12/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "History.h"

History::History(int nRows, int nCols){
    
}

bool History::record(int r, int c){
    if (r<0 || r>MAXROWS || c<0 || c>MAXCOLS)
        return false;
    
    
    return true;
}

void History::display() const{
    
}

