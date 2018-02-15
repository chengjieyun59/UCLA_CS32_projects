//
//  main.cpp
//  Homework3 #3 maze recursive
//
//  Created by Jie-Yun Cheng on 2/13/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// (Our convention is that (0,0) is the northwest (upper left) corner, with south (down) being the increasing r direction and east (right) being the increasing c direction.)

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)     // If the current (r,c) coordinate is equal to the ending coordinate,
        return true;            // then we've solved the maze so return true!
 
    maze[sr][sc] = '#'; // simplify problem by dropping bread crumb
    // cout << "(" << sr << "," << sc << "), "; // prints out (4,3), (3,3), (5,3), (5,2), (5,1), (6,1), (7,1), (8,1), (8,2), (6,3), (4,4), (4,5), (5,5), (6,5), (6,6), (7,6), (8,6), (8,5), (8,4), (4,6), (4,7), (4,8), (3,8), (2,8), (1,8), Solvable!

    // CAN MOVE NORTH
    if (maze[sr-1][sc] != '#' && maze[sr-1][sc] != 'X' && maze[sr-1][sc] == '.' && sr > 0)
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec) == true)
            return true;
    
    // CAN MOVE WEST
    if (maze[sr][sc-1] != '#' && maze[sr][sc-1] != 'X' && maze[sr][sc-1] == '.' && sc > 0)
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec) == true)
            return true;
    
    // CAN MOVE SOUTH
    if (maze[sr+1][sc] != '#' && maze[sr+1][sc] != 'X' && maze[sr+1][sc] == '.' && sr < nRows)
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec) == true)
            return true;
    
    // CAN MOVE EAST
    if (maze[sr][sc+1] != '#' && maze[sr][sc+1] != 'X' && maze[sr][sc+1] == '.' && sc < nCols)
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec) == true)
            return true;

    return false;
    
    /* recursive pseudocode
    If the start location is equal to the ending location, then we've solved the maze, so return true.
    Mark the start location as visted.
    For each of the four directions,
        If the location one step in that direction (from the start location) is unvisited,
            then call pathExists starting from that location (and ending at the same ending location as in the current call).
            If that returned true,
                then return true.
    Return false.
    (If you wish, you can implement the pseudocode for loop with a series of four if statements instead of a loop.)
    */

}
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise

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
