#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <vector>
#include <string>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    /* Hint:
     void zapAllZappableActors(int x, int y) {
        for (p = actors.begin(); p != actors.end(); p++)
            if (p->isAt(x,y) && p->isZappable())
                p->zap();
     }
     */

private:
    vector<Actor*> m_vActor;
    NachenBlaster* m_NachenBlaster;
};

#endif // STUDENTWORLD_H_
