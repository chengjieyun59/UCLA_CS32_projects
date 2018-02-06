//
//  main.cpp
//  Homework2 #3 mazequeue
//
//  Created by Jie-Yun Cheng on 2/3/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <string>
#include <queue>
#include <iostream>
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
    queue<Coord> coordQueue;        // declare a queue of Coords
    coordQueue.push(Coord(sr,sc));  // Push the starting coordinate (sr,sc) onto the queue
    maze[sr][sc] = '#';             // Mark the starting point as “discovered.”
    
    while (!coordQueue.empty())     // while the queue is not empty
    {
        Coord curr = coordQueue.front();
        int r = curr.r();           // get the current front item's row and column
        int c = curr.c();
        coordQueue.pop();           // remove the front item from stack
        
        if (r == er && c == ec)     // If the current (r,c) coordinate is equal to the ending coordinate,
            return true;            // then we've solved the maze so return true!
        
        // If you can move EAST/SOUTH/WEST/NORTH and haven't encountered that cell yet, then push the coordinate (r+/-1,c+/-1) onto the stack, and update maze[r+/-1][c+/-1] to indicate the algorithm has encountered it.
        if (maze[r][c+1] != '#' && maze[r][c+1] != 'X' && maze[r][c+1] == '.' && c < nCols)
        {
            coordQueue.push(Coord(r, c+1));
            maze[r][c+1] = '#';
        } // CAN MOVE EAST
        
        if (maze[r+1][c] != '#' && maze[r+1][c] != 'X' && maze[r+1][c] == '.' && r < nRows)
        {
            coordQueue.push(Coord(r+1, c));
            maze[r+1][c] = '#';
        } // CAN MOVE SOUTH
        
        if (maze[r][c-1] != '#' && maze[r][c-1] != 'X' && maze[r][c-1] == '.' && c > 0)
        {
            coordQueue.push(Coord(r, c-1));
            maze[r][c-1] = '#';
        } // CAN MOVE WEST
        
        if (maze[r-1][c] != '#' && maze[r-1][c] != 'X' && maze[r-1][c] == '.' && r > 0)
        {
            coordQueue.push(Coord(r-1, c));
            maze[r-1][c] = '#';
        } // CAN MOVE NORTH
    }
    return false; // If the queue is empty, there is NO SOLUTION and we’re done!
}
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
// Now convert your pathExists function to use a queue instead of a stack, making the fewest changes to achieve this. You may either write your own queue class, or use the queue type from the C++ Standard Library.

// TODO: comment out the main function
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
