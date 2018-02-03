#include <stack>
#include <iostream>
using namespace std;

#include "towers.h"

TowersOfHanoi::TowersOfHanoi() {
    num_disks = 3;
    for (int i = num_disks - 1; i >= 0; --i) {
        m_towers[0].push(i);
    }
    
    printGameState();
}

TowersOfHanoi::TowersOfHanoi(int n) {
    this->num_disks = n;
    for (int i = n - 1; i >= 0; --i) {
        m_towers[0].push(i);
    }
    
    printGameState();
}

// function that doesn't return, but prints some result
// you can move a disk from one tower to any other tower
// as long as you obey the rule that a larger disk (larger
// int) can never be place on top of a smaller disk
void TowersOfHanoi::moveDisk(int fromTower, int toTower) {
    cout << "\n\n\n";
    
    if (fromTower == toTower) {
        cout << "No point in moving a disk to the same tower!\n";
    }
    
    else if (m_towers[fromTower].empty()) {
        cout << "Nothing on that tower to move!\n";
    }
    
    else if (m_towers[toTower].empty()) {
        int fromDisk = m_towers[fromTower].top();
        
        cout << "Moved " << fromDisk << " from tower " << fromTower
        << " to tower " << toTower << " which was empty\n";
        
        m_towers[fromTower].pop();
        m_towers[toTower].push(fromDisk);
    }
    
    
    
    else {
        int fromDisk = m_towers[fromTower].top();
        int toDisk = m_towers[toTower].top();
        
        if (toDisk < fromDisk) {
            cout << "Can't place a larger disk on a smaller disk!\n";
            return;
        }
        
        else {
            cout << "Moved disk sized " << fromDisk << " from tower "
            << fromTower << " to tower " << toTower << " which had "
            << toDisk << " at the top." << endl;
            
            m_towers[fromTower].pop();
            m_towers[toTower].push(fromDisk);
        }
    }
    
    printGameState();
}

void TowersOfHanoi::printGameState() {
    
    // print out each of the towers
    for (int i = 0; i < 3; ++i) {
        cout << i << endl;
        
        stack<int> temp = m_towers[i];
        while (!temp.empty()) {
            int disk_size = temp.top() + 1;
            temp.pop();
            
            // print disk_size X's
            for (int j = 0; j < disk_size; ++j) {
                cout << 'X';
            }
            cout << endl;
        }
        cout << endl;
        
    }
    
    checkWonState();
}

void TowersOfHanoi::checkWonState() {
    // won state
    if (m_towers[0].empty() && m_towers[2].empty()) {
        stack<int> temp = m_towers[1];
        bool won = true;
        
        while (temp.size() > 1) {
            int top = temp.top();
            temp.pop();
            int next = temp.top();
            
            if (top > next) {
                won = false;
            }
        }
        
        if (won) {
            cout << "CONGRATULATIONS YOU WON!!!\n";
        }
    }
}


int main() {
    TowersOfHanoi toh;
    toh.moveDisk(0, 1);
    toh.moveDisk(0, 2);
    toh.moveDisk(1, 2);
    toh.moveDisk(0, 1);
    toh.moveDisk(0, 2);
    toh.moveDisk(2, 0);
    toh.moveDisk(2, 1);
    toh.moveDisk(0, 1);
    
    
    
    return 0;
}





#include <stack>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

//
//
// STACK STUFF
//
//


// correctParens - takes in a stack of chars that (from the bottom up)
// is a string of parens, valid or not

// this function should return true if it's a valid parenthesis string
// and false if not

bool correctParens(stack<char>& s) {
    stack<char> temp;
    
    while (!s.empty()) {
        if (s.top() == ')') {
            
            
            // put all preceding closed parens in stack
            while (s.top() == ')' && !s.empty()) {
                temp.push(s.top());
                s.pop();
            }
            
            // pop one off of temp for each subsequent open you get
            while (!s.empty() && s.top() == '(') {
                temp.pop();
                s.pop();
            }
        }
        
        // if you're ever looking at an open paren
        // without having seen an closed one, it's no good
        else {
            return false;
        }
    }
    
    return temp.empty();
}

// binarytoDecimal
//      if you wanna read binary right to left,
//   push everything into a stack (right goes in last) and
//   pop out one at a time, adding in accordingly
//       BUT if you wanna read left to right ... you can use a
//       queue and read the front then pop
// little endian: least significant value is stored first
//         so you read it left to right -- QUEUE
// big endian: most significant value is stored first
//        so you read it right to left -- STACK

int binaryToDecimal(string s) {
    
    // need to convert string to stack of 1's and 0's
    
    // push all of the bits into a stack so that you
    // can easily read them backwards and add in 2^pos
    // or not
    stack<int> binary; // change to queue if little endian
    for (int i = 0; i < s.size(); ++i) {
        binary.push(int(s[i]) - 48);
    }
    
    int pos = 0;
    int ret = 0;
    
    // run through the stack, adding in 2^pos if 1 or not
    while (!binary.empty()) {
        if (binary.top() == 1) { // change to front if little endian
            ret += pow(2, pos);
        }
        
        binary.pop();
        ++pos;
    }
    
    return ret;
}

//
//
// QUEUE STUFF
//
//

// this function takes in n, a number of people
// and m, meaning each mth person will be killed
// until there is just one person left
void dontGetKilled(int m, int n) {
    queue<int> s;
    
    // push all of the people into a queue
    for (int i = 0; i < n; ++i) {
        s.push(i);
    }
    
    // you know all of the positions that are going to be killed
    // by printing and popping every m people until the queue is empty
    // the last person's position to be printed is not going to die
    while (!s.empty()) {
        
        // to avoid modulus, we can keep a countdown of people
        // to not kill and once that's 0, kill that person
        int betweeners = m - 1;
        while (betweeners != 0) {
            
            // every
            s.push(s.front());
            s.pop();
            --betweeners;
        }
        
        // kill the mth person - print them out and
        // take them out of the queue
        cout << s.front() << " " ;
        s.pop();
    }
    cout << endl;
}
