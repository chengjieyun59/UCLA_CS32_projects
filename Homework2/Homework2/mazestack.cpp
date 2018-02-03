//
//  mazestack.cpp
//  Homework2
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
     stack<Coord> coordStack;     // declare a stack of Coords
     
     Coord a(5,6);
     coordStack.push(a);             // push the coordinate (5,6)
     coordStack.push(Coord(3,4));    // push the coordinate (3,4)
     
     Coord b = coordStack.top();     // look at top item in the stack
     coordStack.pop();               // remove the top item from stack
     if (coordStack.empty())         // Is the stack empty?
     cout << "empty!" << endl;
     cout << coordStack.size() << endl;  // num of elements
     */
    
    /* pseudocode:
     Push the starting coordinate (sr,sc) onto the coordinate stack and
     update maze[sr][sc] to indicate that the algorithm has encountered
     it (i.e., set maze[sr][sc] to have a value other than '.').
     While the stack is not empty,
     {   Pop the top coordinate off the stack. This gives you the current
     (r,c) location that your algorithm is exploring.
     If the current (r,c) coordinate is equal to the ending coordinate,
     then we've solved the maze so return true!
     Check each place you can move from the current cell as follows:
     If you can move EAST and haven't encountered that cell yet,
     then push the coordinate (r,c+1) onto the stack and update
     maze[r][c+1] to indicate the algorithm has encountered it.
     If you can move SOUTH and haven't encountered that cell yet,
     then push the coordinate (r+1,c) onto the stack and update
     maze[r+1][c] to indicate the algorithm has encountered it.
     If you can move WEST and haven't encountered that cell yet,
     then push the coordinate (r,c-1) onto the stack and update
     maze[r][c-1] to indicate the algorithm has encountered it.
     If you can move NORTH and haven't encountered that cell yet,
     then push the coordinate (r-1,c) onto the stack and update
     maze[r-1][c] to indicate the algorithm has encountered it.
     }
     There was no solution, so return false
     */
    return true;
}
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
// Your implementation must use a stack data structure, specifically, a stack of Coords. You may either write your own stack class, or use the stack type from the C++ Standard Library.

// TODO: comment out the main function
#include <iostream>
#include <stack>
#include <string>
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
