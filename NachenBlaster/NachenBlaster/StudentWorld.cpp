#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
// include STL data sturctures
#include <vector>
/*
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
*/

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), m_NachenBlaster(nullptr)// , m_vActor(0) // vectors have default constructors
{}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    NachenBlaster* nb = new NachenBlaster(this);
    m_vActor.push_back(nb); // create a NachenBlaster and add to Actor vector
    
    // create 30 stars
    for (int i = 0; i < 30; i++)
    {
        Star* s = new Star(this, randInt(0, VIEW_WIDTH-1));
        m_vActor.push_back(s);
    }
    
    return GWSTATUS_CONTINUE_GAME;
} // spec page 16

int StudentWorld::move()
{
    vector<Actor*>::iterator a;
    
    // if actor is alive, call the doSomething() for every Actor (NachenBlaster, Stars, aliens, etc.)
    for(a = m_vActor.begin(); a != m_vActor.end();a++)
    {
        if((*a)->isAlive())
        {
            (*a)->doSomething();
            /*
            if (theNachenBlasterDiedDuringThisTick())
                return GWSTATUS_PLAYER_DIED;
            if (theNachenBlasterCompletedTheCurrentLevel()) {
                increaseScoreAppropriately();
                return GWSTATUS_FINISHED_LEVEL;
             */
            
        }
    }
    // It is possible that one actor (e.g., a cabbage projectile) may destroy another actor (e.g., a Smallgon) during the current tick. If an actor has died earlier in the current tick, then the dead actor must not have a chance to do something during the current tick (since it’s dead).
    
    // Remove newly-dead actors after each tick
    // if actor is dead, delete the dead actors
    // auto keyword is suggested by TA Jason Mao
    for(auto a2 = m_vActor.begin(); a2 != m_vActor.end();)
    {
        if((*a2)->isAlive() == false)
        {
            delete *a2; // delete the pointer first
            a2 = m_vActor.erase(a2); // delete the object that the pointer pointed to
        }
        else a2++;
    }
    
    // Possibly create a new star on the far right side on a 1/15 chance
    if (randInt(0, 14) == 0)
        m_vActor.push_back(new Star(this, VIEW_WIDTH-1));
    
    /*
    // Update the Game Status Line
    updateDisplayText(); // update the score/lives/level text at screen top
    */
    
    return GWSTATUS_CONTINUE_GAME;
} // spec page 17

void StudentWorld::cleanUp()
{
    // delete NachenBlaster player
    if (m_NachenBlaster != nullptr)
    {
        delete m_NachenBlaster;
        m_NachenBlaster = nullptr;
    }
    
    // delete all other actors
    vector<Actor*>::iterator a;
    for(a = m_vActor.begin(); a != m_vActor.end();)
    {
        delete *a;
        a = m_vActor.erase(a);
    }
    
} // Every actor in the entire game (the NachenBlaster and every alien, goodie, projectile, star, explosion object, etc.) must be deleted and removed from the StudentWorld’s container of active objects, resulting in an empty level. NachenBlaster lost a life (e.g., its hit points reached zero due to being shot) or has completed the current level
