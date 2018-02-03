//
//  main.cpp
//  Homework2 #3 mazequeue
//
//  Created by Jie-Yun Cheng on 2/3/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <string>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};
// (Our convention is that (0,0) is the northwest (upper left) corner, with south (down) being the increasing r direction and east (right) being the increasing c direction.)

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    
    return true;
}
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
// Now convert your pathExists function to use a queue instead of a stack, making the fewest changes to achieve this. You may either write your own queue class, or use the queue type from the C++ Standard Library.

// TODO: comment out the main function
#include <queue>
#include <iostream>
using namespace std;

int main()
{
    queue<Coord> coordQueue;    // declare a queue of Coords
    
    Coord a(5,6);
    coordQueue.push(a);            // enqueue item at back of queue
    coordQueue.push(Coord(3,4));   // enqueue item at back of queue

    Coord b = coordQueue.front();  // look at front item
    coordQueue.pop();              // remove the front item from queue
    if (coordQueue.empty())        // Is the queue empty?
        cout << "empty!" << endl;
    cout << coordQueue.size() << endl;  // num of elements
}
