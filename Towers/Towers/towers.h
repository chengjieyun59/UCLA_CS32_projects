#ifndef TOWERS_H
#define TOWERS_H

class TowersOfHanoi {
public:
    TowersOfHanoi();
    TowersOfHanoi(const int n);
    void moveDisk(int fromTower, int toTower);
    
private:
    stack<int> m_towers[3];
    int num_disks;
    
    void printGameState();
    void checkWonState();
};


#endif
