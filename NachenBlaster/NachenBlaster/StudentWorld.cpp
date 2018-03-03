// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>  // defines the type std::ostringstream
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), m_NachenBlaster(nullptr)
{}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    // create the player
    m_NachenBlaster = new NachenBlaster(this);
    
    // variables for creating new aliens
    m_AlienDestroyed = 0;
    m_CurrentAlienOnScreen = 0;
    m_RemainingAlienToDestroy = 6 + 4 * getLevel() - m_AlienDestroyed;
    m_MaxAlienOnScreen = 4 + (0.5 * getLevel());
    S1 = 60;
    S2 = 20 + getLevel() * 5;
    S3 = 5 + getLevel() * 10;
    S = S1+S2+S3;
    
    // create 30 stars
    for (int i = 0; i < 30; i++)
    {
        Star* s = new Star(this, randInt(0, VIEW_WIDTH-1));
        m_vActor.push_back(s);
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // every actor needs to do something
    if(m_NachenBlaster->isAlive())
        m_NachenBlaster->doSomething();
    vector<Actor*>::iterator a;
    for(a = m_vActor.begin(); a != m_vActor.end();a++)
    {
        if((*a)->isAlive() == true)
            (*a)->doSomething();
        if(m_NachenBlaster->isAlive() == false)
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        if(m_AlienDestroyed >= 6+4*getLevel())
            return GWSTATUS_FINISHED_LEVEL;
    }
    
    // It is possible that one actor may destroy another actor during the current tick, so remove newly-dead actors after each tick.
    // auto keyword is suggested by TA Jason Mao
    for(auto a2 = m_vActor.begin(); a2 != m_vActor.end();) 
    {
        if((*a2)->isAlive() == false)
        {
            if((*a2)->isAlien())
                m_CurrentAlienOnScreen--;
            delete *a2; // delete the pointer first
            a2 = m_vActor.erase(a2); // delete the object that the pointer pointed to
        }
        else
            a2++;
    }
    
    // Create a new star
    if (randInt(1, 15) == 1)
        m_vActor.push_back(new Star(this, VIEW_WIDTH-1));
    
    // Create new aliens
    m_RemainingAlienToDestroy = 6 + 4 * getLevel() - m_AlienDestroyed;
    if(m_CurrentAlienOnScreen < min(m_MaxAlienOnScreen, m_RemainingAlienToDestroy))
    {
        // always create just one alien
        int rand = randInt(1, S);
        if(rand <= S1) // probability S1/S
        {
            m_vActor.push_back(new Smallgon(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
            m_CurrentAlienOnScreen++;
        }
        else if(rand <= S1 + S2) // probability S2/S
        {
            m_vActor.push_back(new Smoregon(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
            m_CurrentAlienOnScreen++;
        }
        else // if(rand <= S1 + S2 + S3) // probability S3/S
        {
            m_vActor.push_back(new Snagglegon(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
            m_CurrentAlienOnScreen++;
        }
    }
    
    // Update the Game Status Line
    stringstream s;
    s <<"Lives: " << (int)getLives() << "  Health: " << (int)m_NachenBlaster->healthPercentage() << "%  Score: " << (int)getScore() << " Level: " << (int)getLevel() << "  Cabbages: " << (int)m_NachenBlaster->cabbagePercentage() << "% Torpedoes: " << (int)m_NachenBlaster->getTorpedoPt();
    setGameStatText(s.str());
    
    return GWSTATUS_CONTINUE_GAME;
}

// Every actor in the entire game must be deleted and removed from the StudentWorld’s container of active objects, resulting in an empty level. NachenBlaster lost a life or has completed the current level
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
    for(a = m_vActor.begin(); a != m_vActor.end(); )
    {
        if((*a) != nullptr)
        {
            delete *a;
            *a = nullptr;
            a = m_vActor.erase(a);
        }
    }
}

NachenBlaster* StudentWorld::getNachenBlaster()
{
    return m_NachenBlaster;
}

// If the player has collided with a, return a pointer to the player; otherwise, return a null pointer.
NachenBlaster* StudentWorld::getCollidingPlayer(const Actor* a) const
{
    double xsquare = (a->getX() - m_NachenBlaster->getX()) * (a->getX() - m_NachenBlaster->getX());
    double ysquare = (a->getY() - m_NachenBlaster->getY()) * (a->getY() - m_NachenBlaster->getY());
    double euclidian_dist = sqrt(xsquare + ysquare);
    if(euclidian_dist < 0.75 * (a->getRadius() + m_NachenBlaster->getRadius()))
        return m_NachenBlaster;
    return nullptr;
}

// If there's at least one alien that's collided with a, return a pointer to one of them; otherwise, return a null pointer.
Alien* StudentWorld::getOneCollidingAlien(const Actor* a) const
{
    for(auto b = m_vActor.begin(); b != m_vActor.end();b++)
    {
        if((*b)->isAlien())
        {
            double xsquare = (a->getX() - (*b)->getX()) * (a->getX() - (*b)->getX());
            double ysquare = (a->getY() - (*b)->getY()) * (a->getY() - (*b)->getY());
            double euclidian_dist = sqrt(xsquare + ysquare);
            if(euclidian_dist < 0.75 * (a->getRadius() + (*b)->getRadius()))
                return (Alien *)*b; // cast an actor pointer into an alien pointer. b is an iterator. Need to return a pointer. Get the object, an actor pointer.
        }
    }
    return nullptr;
}

// An alien may attack if a player is in line of fire
bool StudentWorld::playerInLineOfFire(const Actor* a) const
{
    if(a->getY() == m_NachenBlaster->getY() && m_NachenBlaster->getY()-4 <= a->getY() && m_NachenBlaster->getY()+4 >= a->getY())
        return true;
    return false;
}

// Add an actor to the world.
void StudentWorld::addActor(Actor* a)
{
    m_vActor.push_back(a);
}

// Record that one more alien on the current level has been destroyed.
void StudentWorld::recordAlienDestroyed()
{
    m_AlienDestroyed++;
}
