// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <vector>
#include <string>
using namespace std;

class Actor;
class Player;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    // accessors
    NachenBlaster* getNachenBlaster();
    NachenBlaster* getCollidingPlayer(const Actor* a) const;
    Alien* getOneCollidingAlien(const Actor* a) const;
    bool playerInLineOfFire(const Actor* a) const;
    // mutators
    void addActor(Actor* a);
    void recordAlienDestroyed();
    
private:
    vector<Actor*> m_vActor;
    NachenBlaster* m_NachenBlaster;
    int m_AlienDestroyed, m_RemainingAlienToDestroy, m_MaxAlienOnScreen, m_CurrentAlienOnScreen;
    int S1, S2, S3, S;
};

#endif // STUDENTWORLD_H_
