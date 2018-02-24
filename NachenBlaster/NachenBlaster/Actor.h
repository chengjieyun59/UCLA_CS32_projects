#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class GameWorld;
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* World, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0);
    virtual ~Actor();
    virtual void doSomething() = 0; // move around, cause damage, grant bonuses, etc.
    bool isInBound(int x, int y);
    bool isAlive();
    virtual void setAlive(std::string aliveStatus);
    StudentWorld* getWorld();
    
private:
    bool m_isAlive;
    StudentWorld* m_world;
    
}; // Each actor has its own x,y location in space, its own internal state (e.g., a Snagglegon knows its location, what direction it’s moving, etc.) and its own special algorithms that control its actions in the game based on its own state and the state of the other objects in the world.

class Star: public Actor
{
public:
    Star(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Star();
    virtual void doSomething();
}; // page 26

class NachenBlaster: public Actor
{
public:
    NachenBlaster(StudentWorld* world);
    //instead of NachenBlaster(int imageID, double startX, double startY, int dir, double size, int depth, double hitPoint, double cabbagePoint);
    virtual ~NachenBlaster();
    virtual void doSomething();
    void attacked();
    
protected:
    void incHitPt(int howMuch);
    void decHitPt(int howMuch);
    int getHitPt() const;
    
    void incCabbagePt(int howMuch);
    void dcCabbagePt(int howMuch);
    int getCabbagePt() const;
    
private:
    int m_hitPt;
    int m_cabbagePt;
}; // the algorithm that controls the ship object is the user’s own brain and hand, and the keyboard
// page 23-25

class Explosion: public Actor
{
public:
    Explosion(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Explosion();
    virtual void doSomething();
    double getSize();
    void setSize(int sizeStatus);

private:
    int m_size;
};

///////////
// Alien //
///////////

class Alien: public Actor
{
public:
    Alien();
    virtual ~Alien();
    virtual void doSomething()=0; // Hint: studentWorldPtr->zapAllZappableActors(getX(), getY());
    virtual void attacked() = 0;
    
private:
    
};

class Smallgon: public Alien
{
public:
    Smallgon();
    virtual ~Smallgon();
    virtual void doSomething();
    virtual void attacked();
    
private:
    
};

class Smoregon: public Alien
{
public:
    Smoregon();
    virtual ~Smoregon();
    virtual void doSomething();
    virtual void attacked();
    
private:
    
};

class Snagglegon: public Alien
{
public:
    Snagglegon();
    virtual ~Snagglegon();
    virtual void doSomething();
    virtual void attacked();
    
private:
    
};

////////////////
// Projectile //
////////////////

class Projectile: public Actor
{
public:
    Projectile(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Projectile();
    virtual void doSomething()=0;
    double getDir();
    void setDir(int dirStatus);
    
private:
    int m_dir;
    
};

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~Cabbage();
    virtual void doSomething();
    
private:
    
};

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~Turnip();
    virtual void doSomething();
    
private:
    
};

class Torpedo: public Projectile
{
public:
    Torpedo(StudentWorld* World, int imageID, double startX, double startY, int dir);
    virtual ~Torpedo();
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
    virtual void doSomething()=0;
    
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