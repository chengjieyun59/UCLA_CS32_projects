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

int StudentWorld::init()
{
    
    return GWSTATUS_CONTINUE_GAME;
} // spec page 16

int StudentWorld::move()
{
    
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
    // every actor in the entire game (the NachenBlaster and every alien, goodie, projectile, star, explosion object, etc.) must be deleted and removed from the StudentWorld’s container of active objects, resulting in an empty level.
} // NachenBlaster lost a life (e.g., its hit points reached zero due to being shot) or has completed the current level
