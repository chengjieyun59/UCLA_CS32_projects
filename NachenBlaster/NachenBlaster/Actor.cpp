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

