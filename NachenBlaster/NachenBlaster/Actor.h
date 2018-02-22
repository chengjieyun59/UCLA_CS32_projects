#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0)
    :GraphObject(imageID, startX, startY, dir, size, depth)
    {} // page 22 // todo: imageID isn't always IID_NACHENBLASTER
    
    virtual ~Actor();
    virtual void doSomething() = 0; // move around, cause damage, grant bonuses, etc.
    // virtual void attacked() = 0;
    // bool isAlive() = 0;
    
    // may need to use GraphObject's functions: getX(); getY(); moveTo(double x, double y); setSize(double size);
    
private:
    bool m_isAlive;
}; // Each actor has its own x,y location in space, its own internal state (e.g., a Snagglegon knows its location, what direction it’s moving, etc.) and its own special algorithms that control its actions in the game based on its own state and the state of the other objects in the world.

class Star: public Actor
{
public:
    Star();
    virtual ~Star();
    virtual void doSomething();
    
private:
    
}; // page 26

class NachenBlaster: public Actor
{
public:
    NachenBlaster(int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0)
    :Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0), m_hitPoints(50), m_cabbagePoints(30)
    {}
    virtual ~NachenBlaster();
    virtual void doSomething();
    
private:
    int m_hitPoints;
    int m_cabbagePoints;
}; // the algorithm that controls the ship object is the user’s own brain and hand, and the keyboard
// page 23-25

class Explosion: public Actor
{
public:
    Explosion();
    virtual ~Explosion();
    virtual void doSomething();
    
private:
    
}; //

///////////
// Alien //
///////////

class Alien: public Actor
{
public:
    Alien();
    virtual ~Alien();
    virtual void doSomething();
    
private:
    
};

class Smallgon: public Alien
{
public:
    Smallgon();
    virtual ~Smallgon();
    virtual void doSomething();
    
private:
    
};

class Smoregon: public Alien
{
public:
    Smoregon();
    virtual ~Smoregon();
    virtual void doSomething();
    
private:
    
};

class Snagglegon: public Alien
{
public:
    Snagglegon();
    virtual ~Snagglegon();
    virtual void doSomething();
    
private:
    
};

////////////////
// Projectile //
////////////////

class Projectile: public Actor
{
public:
    Projectile();
    virtual ~Projectile();
    virtual void doSomething();
    
private:
    
};

class Cabbage: public Projectile
{
public:
    Cabbage();
    virtual ~Cabbage();
    virtual void doSomething();
    
private:
    
};

class Turnip: public Projectile
{
public:
    Turnip();
    virtual ~Turnip();
    virtual void doSomething();
    
private:
    
};

class FlatulenceTorpedo: public Projectile
{
public:
    FlatulenceTorpedo();
    virtual ~FlatulenceTorpedo();
    virtual void doSomething();
    
private:
    
};

////////////
// Goodie //
////////////

class Goodie: public Actor
{
public:
    Goodie();
    virtual ~Goodie();
    virtual void doSomething();
    
private:
    
};

class RGoodie: public Goodie // repair goodies
{
public:
    RGoodie();
    virtual ~RGoodie();
    virtual void doSomething();
    
private:
    
};

class ELGoodie: public Goodie // extra life goodies
{
public:
    ELGoodie();
    virtual ~ELGoodie();
    virtual void doSomething();
    
private:
    
};

class FTGoodie: public Goodie // flatulence torpedo goodies
{
public:
    FTGoodie();
    virtual ~FTGoodie();
    virtual void doSomething();
    
private:
    
};

#endif // ACTOR_H_
