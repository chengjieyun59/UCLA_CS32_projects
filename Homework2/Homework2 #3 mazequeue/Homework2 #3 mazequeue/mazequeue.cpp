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
    
    /*
     Nachenberg's slide:
     1.   Insert starting point onto the queue.
     2.  Mark the starting point as “discovered.”
     3.  If the queue is empty, there is    NO SOLUTION and we’re done!
     4.  Remove the top point from the queue.
     5.  If we’re at the endpoint, DONE!  Otherwise…
     6.  If slot to the WEST is open & is undiscovered
            Mark (curx-1,cury) as “discovered”
            INSERT (curx-1,cury) on queue.
     7.  If slot to the EAST is open & is undiscovered
            Mark (curx+1,cury) as “discovered”
            INSERT (curx+1,cury) on queue.
     8.  If slot to the NORTH is open & is undiscovered
            Mark (curx,cury-1) as “discovered”
            INSERT (curx,cury-1) on queue.
     9.  If slot to the SOUTH is open & is undiscovered
            Mark (curx,cury+1) as “discovered”
            INSERT (curx,cury+1) on queue.
     10. GOTO step #3
     */
    
    /*
     queue<Coord> coordQueue;    // declare a queue of Coords
     
     Coord a(5,6);
     coordQueue.push(a);            // enqueue item at back of queue
     coordQueue.push(Coord(3,4));   // enqueue item at back of queue
     
     Coord b = coordQueue.front();  // look at front item
     coordQueue.pop();              // remove the front item from queue
     if (coordQueue.empty())        // Is the queue empty?
     cout << "empty!" << endl;
     cout << coordQueue.size() << endl;  // num of elements
     */
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
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
