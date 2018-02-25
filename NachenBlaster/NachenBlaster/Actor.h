#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class GameWorld;
class StudentWorld;
//class GameController;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* World, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0);
    virtual ~Actor();
    virtual void doSomething() = 0; // move around, cause damage, grant bonuses, etc.
    virtual void attacked() = 0;
    bool isInBound(int x, int y);
    bool isAlive();
    virtual void setAlive(std::string aliveStatus);
    double euclidian_dist(double x1, double y1, double x2, double y2);
    StudentWorld* getWorld();
    //GameController* getControl();
    
private:
    bool m_isAlive;
    StudentWorld* m_world;
    //GameController* m_control;
    
}; // Each actor has its own x,y location in space, its own internal state (e.g., a Snagglegon knows its location, what direction it’s moving, etc.) and its own special algorithms that control its actions in the game based on its own state and the state of the other objects in the world.

class Star: public Actor
{
public:
    Star(StudentWorld* World, double startX);
    virtual ~Star();
    virtual void doSomething();
    virtual void attacked();
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
    void setHitPt(int newHitPt);
    int getHitPt() const;
    
    void setCabbagePt(int newCabbagePt);
    int getCabbagePt() const;
    
    void setTorpedoPt(int newTorpedoPt);
    int getTorpedoPt() const;
    
private:
    int m_hitPt;
    int m_cabbagePt;
    int m_torpedoPt;
}; // the algorithm that controls the ship object is the user’s own brain and hand, and the keyboard
// page 23-25

class Explosion: public Actor
{
public:
    Explosion(StudentWorld* World, double startX, double startY, double size);
    virtual ~Explosion();
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
    Projectile(StudentWorld* World, int imageID, double startX, double startY, int dir);
    virtual ~Projectile();
    virtual void doSomething()=0;
    virtual void attacked();

private:

};

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld* World, double startX, double startY);
    virtual ~Cabbage();
    virtual void doSomething();

private:
    
};

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld* World, double startX, double startY);
    virtual ~Turnip();
    virtual void doSomething();

private:
    
};

class Torpedo: public Projectile
{
public:
    Torpedo(StudentWorld* World, double startX, double startY, int dir);
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
    Goodie(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Goodie();
    virtual void doSomething();
    virtual void attacked();

private:
    virtual void doDiffGoodieThing() = 0;
};


class ELGoodie: public Goodie // extra life goodies
{
public:
    ELGoodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~ELGoodie();

private:
    virtual void doDiffGoodieThing();
};

class RGoodie: public Goodie // repair goodies
{
public:
    RGoodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~RGoodie();

private:
    virtual void doDiffGoodieThing();
};

class FTGoodie: public Goodie // flatulence torpedo goodies
{
public:
    FTGoodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~FTGoodie();

private:
    virtual void doDiffGoodieThing();
};

///////////
// Alien //
///////////

class Alien: public Actor
{
public:
    Alien(StudentWorld* World, int level, int imageID, double startX, double startY, int dir, double size, int depth, int hitPoint, int flightLength, double speed);
    virtual ~Alien();
    virtual void doSomething()=0; // Hint: studentWorldPtr->zapAllZappableActors(getX(), getY());
    virtual void attacked() = 0;
    
private:
    int m_hitpoints;
    int m_flightlength;
    double m_speed;
    int m_level;
};

class Smallgon: public Alien
{
public:
    Smallgon(StudentWorld* World, int level, int imageID, double startX, double startY, int hitPoint, int flightLength, double speed);
    virtual ~Smallgon();
    virtual void doSomething();
    virtual void attacked();
    
private:

    
};

class Smoregon: public Alien
{
public:
    Smoregon(StudentWorld* World, int level, int imageID, double startX, double startY, int hitPoint, int flightLength, double speed);
    virtual ~Smoregon();
    virtual void doSomething();
    virtual void attacked();
    
private:
    
};

class Snagglegon: public Alien
{
public:
    Snagglegon(StudentWorld* World, int level, int imageID, double startX, double startY, int hitPoint, int flightLength, double speed);
    virtual ~Snagglegon();
    virtual void doSomething();
    virtual void attacked();
    
private:
    
};

#endif // ACTOR_H_
