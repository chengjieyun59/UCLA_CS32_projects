#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>

// include STL data sturctures
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    for (int i = 0; i < 30; i++)
        m_vStar.push_back(new Star(IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0, randInt(5, 50)/100.0, 3));
    
    return GWSTATUS_CONTINUE_GAME;
} // spec page 16

int StudentWorld::move()
{
    for(int i = 0; i < m_vStar.size(); i++)
    {
        if(m_vStar[i] -> isAlive() == true)
            m_vStar[i] -> doSomething();
        
        else // if the star moves off the screen, delete it
        {
            vector<Star*>::iterator s = m_vStar.begin();
            delete *(s+i);
            s = m_vStar.erase(m_vStar.begin() + i);
        }
    }
    
    // Each tick, there is a 1/15 chance a new star is created
    int n = randInt(0, 14);
    if (n == 0)
        m_vStar.push_back(new Star(IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0, randInt(5, 50)/100.0, 3));
    
    
    /*
    // Pseudocode:
    // The term "actors" refers to all aliens, the NachenBlaster, goodies, // stars, explosions, projectiles, stars, etc.
    // Give each actor a chance to do something, incl. the NachenBlaster
    for each of the actors in the game world { // iterate over active actor that’s active in the game
        if (actor[i] is still active/alive) {
            // tell each actor to do something (e.g. move)
            actor[i]->doSomething();
            
            if (theNachenBlasterDiedDuringThisTick())
                return GWSTATUS_PLAYER_DIED;
            if (theNachenBlasterCompletedTheCurrentLevel()) {
                increaseScoreAppropriately();
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    // It is possible that one actor (e.g., a cabbage projectile) may destroy another actor (e.g., a Smallgon) during the current tick. If an actor has died earlier in the current tick, then the dead actor must not have a chance to do something during the current tick (since it’s dead).
    // Remove newly-dead actors after each tick
    removeDeadGameObjects(); // delete dead game objects
    // Update the Game Status Line
    updateDisplayText(); // update the score/lives/level text at screen top
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level return GWSTATUS_CONTINUE_GAME;
    */
    return GWSTATUS_CONTINUE_GAME;
} // spec page 17

void StudentWorld::cleanUp()
{
    for(vector<Star*>::iterator s = m_vStar.begin(); s != m_vStar.end(); )
    {
        delete *s;
        s = m_vStar.erase(s);
    }
    // every actor in the entire game (the NachenBlaster and every alien, goodie, projectile, star, explosion object, etc.) must be deleted and removed from the StudentWorld’s container of active objects, resulting in an empty level.
} // NachenBlaster lost a life (e.g., its hit points reached zero due to being shot) or has completed the current level
