#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_isAlive(true)
{} // page 22 // todo: IDs: IID_NACHENBLASTER IID_SMALLGON IID_SMOREGON IID_SNAGGLEGON IID_REPAIR_GOODIE IID_LIFE_GOODIE IID_TORPEDO_GOODIE IID_TORPEDO IID_TURNIP IID_CABBAGE IID_STAR IID_EXPLOSION

Actor::~Actor()
{}

bool Actor::isInBound(int x, int y)
{
    if (x <= VIEW_WIDTH && x >= 0 && y <= VIEW_HEIGHT && y >= 0)
        return true;
    return false;
}

bool Actor::isAlive()
{
    if (isInBound(getX(), getY()) == true)
        m_isAlive = true;
    else
        m_isAlive = false;
    
    return m_isAlive;
}

Star::Star(int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0, randInt(5, 50)/100.0, 3)
{}

Star::~Star()
{}

void Star::doSomething()
{
    double x = getX();
    double y = getY();
    moveTo(x-1, y);
    //if (isAlive == false)
        //StudentWorld::~StudentWorld();
    
}

void Star::attacked()
{} // do nothing

NachenBlaster::NachenBlaster(int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0), m_hitPt(50), m_cabbagePt(30)
{}

NachenBlaster::~NachenBlaster()
{}

void NachenBlaster::doSomething()
{
    
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

