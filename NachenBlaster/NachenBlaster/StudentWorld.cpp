#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

int prevLives = 3;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), m_NachenBlaster(nullptr), m_AlienDestroyed(0)// , m_vActor(0) // vectors have default constructors
{}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

// get a pointer to the vector of actors
vector<Actor*>* StudentWorld::getActorVector()
{
    return &m_vActor;
}

NachenBlaster* StudentWorld::getNachenBlaster()
{
    return m_NachenBlaster;
}

int StudentWorld::init()
{
    NachenBlaster* nb = new NachenBlaster(this);
    m_NachenBlaster = nb;
    m_vActor.push_back(nb); // create a NachenBlaster and add to Actor vector

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
    vector<Actor*>::iterator a;
    
    // if actor is alive, call the doSomething() for every Actor (NachenBlaster, Stars, aliens, etc.)
    for(a = m_vActor.begin(); a != m_vActor.end();a++)
    {
        if((*a)->isAlive())
        {
            (*a)->doSomething();
            
            if(getLives() != prevLives) // NachenBlaster died during this tick
            {
                prevLives = getLives();
                return GWSTATUS_PLAYER_DIED;
            }
            
            if(m_AlienDestroyed >= 6+4*getLevel())
            {
                if((*a)->isSnagglegon())
                    increaseScore(1000);
                else
                    increaseScore(250);
                // advanceToNextLevel();
                return GWSTATUS_FINISHED_LEVEL;
            }
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
    if (randInt(1, 15) == 1)
        m_vActor.push_back(new Star(this, VIEW_WIDTH-1));
    
    // introduce new alien ship
    int R = 6 + 4 * getLevel() - m_AlienDestroyed; // Remaining alien ships that must be destroyed before the level is completed
    int M = 4 + (0.5 * getLevel()); // maximum number of alien ships that should be on the screen at a time
    
    
    int C = 0; // current number of alien ships on the screen
    for(a = m_vActor.begin(); a != m_vActor.end();a++)
    {
        if((*a)->isAlien())
            C++;
    }
    
    if(C < min(M,R))
    {
        int S1 = 60;
        int S2 = 20 + getLevel() * 5;
        int S3 = 5 + getLevel() * 10;
        
        if(randInt(1, 2) == 1) // TODO: placeholder for probability S1/S
            m_vActor.push_back(new Smallgon(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
        if(randInt(1, 3) == 1) // TODO: placeholder for probability S2/S
            m_vActor.push_back(new Smoregon(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
        if(randInt(1, 4) == 1) // TODO: placeholder for probability S3/S
            m_vActor.push_back(new Snagglegon(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
    }

    // Update the Game Status Line
    stringstream s;
    s <<"Lives: " << (int)getLives() << "  Health: " << (int)2*m_NachenBlaster->getHitPt() << "%  Score: " << (int)getScore() << " Level: " << (int)getLevel() << "  Cabbages: " << (int)10*m_NachenBlaster->getCabbagePt()/3 << "% Torpedoes: " << (int)m_NachenBlaster->getTorpedoPt();
    setGameStatText(s.str());

    return GWSTATUS_CONTINUE_GAME;
}

// Every actor in the entire game (the NachenBlaster and every alien, goodie, projectile, star, explosion object, etc.) must be deleted and removed from the StudentWorld’s container of active objects, resulting in an empty level. NachenBlaster lost a life (e.g., its hit points reached zero due to being shot) or has completed the current level
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

// If there's at least one alien that's collided with a, return
// a pointer to one of them; otherwise, return a null pointer.
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
                return (Alien *)*b; // cast an actor pointer into an alien pointer
            // b is an iterator. Need to return a pointer. Get the object, an actor pointer.
        }
    }
    return nullptr;
}

// If the player has collided with a, return a pointer to the player;
// otherwise, return a null pointer.
NachenBlaster* StudentWorld::getCollidingPlayer(const Actor* a) const
{
    double xsquare = (a->getX() - m_NachenBlaster->getX()) * (a->getX() - m_NachenBlaster->getX());
    double ysquare = (a->getY() - m_NachenBlaster->getY()) * (a->getY() - m_NachenBlaster->getY());
    double euclidian_dist = sqrt(xsquare + ysquare);
    
    if(euclidian_dist < 0.75 * (a->getRadius() + m_NachenBlaster->getRadius()))
        return m_NachenBlaster;

    return nullptr;
}

// Is the player in the line of fire of a, which might cause a to attack?
bool StudentWorld::playerInLineOfFire(const Actor* a) const
{
    if(a->getY() == m_NachenBlaster->getY())
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
