#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

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
    
    //vector<Actor*>* getActorVector(); // no longer needed
    NachenBlaster* getNachenBlaster();
    
    // If there's at least one alien that's collided with a, return
    // a pointer to one of them; otherwise, return a null pointer.
    Alien* getOneCollidingAlien(const Actor* a) const;
    
    // If the player has collided with a, return a pointer to the player;
    // otherwise, return a null pointer.
    NachenBlaster* getCollidingPlayer(const Actor* a) const;
    
    // Is the player in the line of fire of a, which might cause a to attack?
    bool playerInLineOfFire(const Actor* a) const;
    
    // Add an actor to the world.
    void addActor(Actor* a);
    
    // Record that one more alien on the current level has been destroyed.
    void recordAlienDestroyed();
    
private:
    vector<Actor*> m_vActor;
    NachenBlaster* m_NachenBlaster;
    int m_AlienDestroyed;
    int m_C; // current number of alien ships on the screen
};

#endif // STUDENTWORLD_H_
