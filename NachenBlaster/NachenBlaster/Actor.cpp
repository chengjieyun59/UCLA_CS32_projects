#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_isAlive(true), m_world(World)
{} // page 22

Actor::~Actor()
{
    // delete getWorld(); // wrong!!!! Delete all the memories that only this class made. Or C++ will try to delete it twice. Bad pointer execution
}

bool Actor::isInBound(int x, int y)
{
    if (x < VIEW_WIDTH && x >= 0 && y < VIEW_HEIGHT && y >= 0)
        return true;
    return false;
}

void Actor::setAlive(string aliveStatus)
{
    if(aliveStatus == "Dead")
        m_isAlive = false;
    else
        m_isAlive = true;
}

bool Actor::isAlive()
{
    if (isInBound(getX(), getY()) == false)
        setAlive("Dead");
    return m_isAlive;
}

StudentWorld* Actor::getWorld()
{
    return m_world;
} // a method in one of its base classes that returns a pointer to a StudentWorld), and then uses this pointer to call the getKey() method.

Star::Star(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(World, IID_STAR, startX, randInt(0, VIEW_HEIGHT-1), 0, randInt(5, 50)/100.0, 3)
{}

Star::~Star()
{} // empty destructor

void Star::doSomething()
{
    moveTo(getX()-1, getY());
}

NachenBlaster::NachenBlaster(StudentWorld* World)
:Actor(World, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0), m_hitPt(50), m_cabbagePt(30)
{}

NachenBlaster::~NachenBlaster()
{}

void NachenBlaster::doSomething()
{
    if (isAlive() == false)
        return;
    else
    {
        int value;
        if(getWorld()->getKey(value))
        {
            double x = getX();
            double y = getY();
            switch (value) {
                case KEY_PRESS_LEFT:   if(isInBound(x-6, y)) moveTo(x-6, y); break;
                case KEY_PRESS_RIGHT:  if(isInBound(x+6, y)) moveTo(x+6, y); break;
                case KEY_PRESS_DOWN:   if(isInBound(x, y-6)) moveTo(x, y-6); break;
                case KEY_PRESS_UP:     if(isInBound(x, y+6)) moveTo(x, y+6); break;
                    // case KEY_PRESS_SPACE: add a cabbage in front of the NachenBlaster...; break;
                    // the NachenBlaster that fires the cabbage must pass in this x,y location when constructing a cabbage object.
                // case KEY_PRESS_ESCAPE: ; break;
                // case KEY_PRESS_TAB: ; break;
                default:
                    break;
            }
        }
    }
} // It must have a limited version of a doSomething() method that lets the user pick a direction by hitting a directional key. If the NachenBlaster hits a directional key during the current tick and this will not cause the NachenBlaster to move off of the space field, it updates the NachenBlaster’s location appropriately. All this doSomething() method has to do is properly adjust the NachenBlaster’s x,y coordinates, and our graphics system will automatically animate its movement it around the space field!

void NachenBlaster::attacked()
{
    
}

void NachenBlaster::incHitPt(int howMuch){m_hitPt += howMuch;}
void NachenBlaster::decHitPt(int howMuch){m_hitPt -= howMuch;}
int NachenBlaster::getHitPt() const {return m_hitPt;}

void NachenBlaster::incCabbagePt(int howMuch){m_cabbagePt += howMuch;}
void NachenBlaster::dcCabbagePt(int howMuch){m_cabbagePt -= howMuch;}
int NachenBlaster::getCabbagePt() const {return m_cabbagePt;}

Explosion::Explosion(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(World, IID_EXPLOSION, startX, startY, 0, size, 0), m_size(size)
{}

Explosion::~Explosion()
{}

void Explosion::setSize(int sizeStatus)
{
    m_size = sizeStatus;
}

double Explosion::getSize()
{
    return m_size;
}

void Explosion::doSomething()
{
    if (getSize() < 6.0)
    {
        setSize(1.5 * getSize());
    } // First four powers of 1.5: 1.5, 2.25, 3.375, 5.0625
    
    if (getSize() == 5.0625)
        setAlive("Dead");
}

Projectile::Projectile(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(World, imageID, startX, startY, 0, 0.5, 1)
{}

Projectile::~Projectile()
{}

void Projectile::setDir(int dirStatus)
{
    m_dir = dirStatus;
}

double Projectile::getDir()
{
    return m_dir;
}

Cabbage::Cabbage(StudentWorld* World, int imageID, double startX, double startY)
:Projectile(World, IID_CABBAGE, startX, startY, 0, 0.5, 1)
{}

Cabbage::~Cabbage(){}

void Cabbage::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if()
     {
     step 3: Otherwise, the cabbage must check to see if it has collided with an alien (see the Euclidian distance check on page 10 of this document). If the cabbage overlaps with an alien (Smoregon, Smallgon or Snagglegon) ship:

     • Damage the victim ship appropriately (by causing the object to lose 2 hit points); the damaged object can then deal with this damage in its own unique way (this may result in the damaged object dying/disappearing, a sound effect being played, the user possibly getting points, etc.) Hint: The cabbage can tell the alien object that it has been damaged by calling a method the alien object has (presumably named sufferDamage or something similar).
     
        setAlive("dead");
        return;
     }
     */
    moveTo(getX()+8, getY());
    setDir(getDir() + 20); // TODO: Check if this is counter-clockwise
    // Finally, after the cabbage has moved itself, the cabbage must AGAIN check to see if has collided with an alien ship, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.), but does not move any further during this tick.
}

Turnip::Turnip(StudentWorld* World, int imageID, double startX, double startY)
:Projectile(World, IID_TURNIP, startX, startY, 0, 0.5, 1)
{}

Turnip::~Turnip()
{}

void Turnip::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if()
     {
     step 3: Otherwise, the turnip must check to see if it has collided with the NachenBlaster (see the Euclidian distance check on page 10 of this document). If the turnip overlaps with the NachenBlaster ship:
     
     • Damage the NachenBlaster appropriately (by causing the object to lose 2 hit
     points); the damaged object can then deal with this damage in its own unique way (this may result in the damaged object dying/disappearing, a sound effect being played, the user possibly getting points, etc.) Hint: The turnip can tell the NachenBlaster that it has been damaged by calling a method the NachenBlaster has (presumably named sufferDamage or something similar).
     
     setAlive("dead");
     return;
     }
     */
    moveTo(getX()-6, getY());
    setDir(getDir() + 20); // TODO: Check if this is counter-clockwise
    // Finally, after the turnip has moved itself, the turnip must AGAIN check to see if has collided with the NachenBlaster, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.), but does not move any further during this tick.
}

Torpedo::Torpedo(StudentWorld* World, int imageID, double startX, double startY, int dir)
:Projectile(World, IID_TORPEDO, startX, startY, dir, 0.5, 1)
{} // TODO: A Flatulence Torpedo has a direction of either 0 degrees (if it was fired by the NachenBlaster) or 180 degrees (if it was fired by a Snagglegon).

Torpedo::~Torpedo()
{}

void Torpedo::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if()
     {
     step 3: Otherwise, the Flatulence Torpedo must check to see if it has collided with an enemy. If the Flatulence Torpedo was fired by a Snagglegon ship, then its only enemy is the NachenBlaster. Otherwise, if the Flatulence Torpedo was fired by the NachenBlaster then its enemy is any alien ship. See the Euclidian distance check on page 10 of this document to determine how to check for collisions. If the Flatulence Torpedo collides with an enemy ship:
     
     • Damage the enemy appropriately (by causing the object to lose 8 hit points); the damaged object can then deal with this damage in its own unique way (this may result in the damaged object dying/disappearing, a sound effect being played, the user possibly getting points, etc.) Hint: The Flatulence Torpedo can tell the enemy object that it has been damaged by calling a method the enemy object has (presumably named sufferDamage or something similar).
     
     setAlive("dead");
     return;
     }
     */
    moveTo(getX()-6, getY()); // TODO: The Flatulence Torpedo must move itself 8 pixels to the left (if it was fired by a Snagglegon) or 8 pixels to the right (if it was fired by the NachenBlaster).
    // Finally, after the Flatulence Torpedo has moved itself, the Flatulence Torpedo must AGAIN check to see if has collided with an enemy, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.), but does not move any further during this tick.
}
