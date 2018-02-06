//
//  mazestack.cpp
//  Homework2
//
//  Created by Jie-Yun Cheng on 2/3/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <iostream>
#include <stack>
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
    stack<Coord> coordStack;        // declare a stack of Coords
    coordStack.push(Coord(sr,sc));  // Push the starting coordinate (sr,sc) onto the coordinate stack
    maze[sr][sc] = '#';             // update maze[sr][sc] to indicate that the algorithm has encountered it
    
    while (!coordStack.empty())     // while the stack is not empty
    {
        Coord curr = coordStack.top();
        int r = curr.r();           // get the current top item's row and column
        int c = curr.c();
        coordStack.pop();           // remove the top item from stack
        
        if (r == er && c == ec)     // If the current (r,c) coordinate is equal to the ending coordinate,
            return true;            // then we've solved the maze so return true!
        
        // If you can move EAST/SOUTH/WEST/NORTH and haven't encountered that cell yet, then push the coordinate (r+/-1,c+/-1) onto the stack, and update maze[r+/-1][c+/-1] to indicate the algorithm has encountered it.
        if (maze[r][c+1] != '#' && maze[r][c+1] != 'X' && maze[r][c+1] == '.' && c < nCols)
        {
            coordStack.push(Coord(r, c+1));
            maze[r][c+1] = '#';
        } // CAN MOVE EAST
        
        if (maze[r+1][c] != '#' && maze[r+1][c] != 'X' && maze[r+1][c] == '.' && r < nRows)
        {
            coordStack.push(Coord(r+1, c));
            maze[r+1][c] = '#';
        } // CAN MOVE SOUTH
        
        if (maze[r][c-1] != '#' && maze[r][c-1] != 'X' && maze[r][c-1] == '.' && c > 0)
        {
            coordStack.push(Coord(r, c-1));
            maze[r][c-1] = '#';
        } // CAN MOVE WEST
        
        if (maze[r-1][c] != '#' && maze[r-1][c] != 'X' && maze[r-1][c] == '.' && r > 0)
        {
            coordStack.push(Coord(r-1, c));
            maze[r-1][c] = '#';
        } // CAN MOVE NORTH
    }
    return false; // if all path are exhausted and haven't arrived at (er,ec) then maze is not solvable
}
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
// Your implementation must use a stack data structure, specifically, a stack of Coords. You may either write your own stack class, or use the stack type from the C++ Standard Library.

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
