// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
using namespace std;

const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;

class StudentWorld;

///////////
// Actor //
///////////

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Actor();
    // accessors
    bool isInBound(int x, int y) const;
    bool isAlive() const;
    virtual bool isAlien() const;
    virtual bool isStar() const;
    virtual bool isNachenBlaster() const;
    virtual bool isSmoregon() const;
    virtual bool isSnagglegon() const;
    virtual bool isProjectile() const;
    virtual bool isTorpedo() const;
    StudentWorld* getWorld() const;
    // mutator
    virtual void setAlive(std::string aliveStatus);
    // pure virtual function
    virtual void doSomething() = 0;
    
private:
    bool m_isAlive;
    StudentWorld* m_world;
};

//////////
// Star //
//////////

class Star: public Actor
{
public:
    Star(StudentWorld* World, double startX);
    virtual ~Star();
    // accessor
    virtual bool isStar() const;
    // mutator
    virtual void doSomething();
    
};

///////////////
// Explosion //
///////////////

class Explosion: public Actor
{
public:
    Explosion(StudentWorld* World, double startX, double startY, double size);
    virtual ~Explosion();
    // mutator
    virtual void doSomething();
};

////////////////////////
// Damageable Objects //
////////////////////////

class DamageableObject: public Actor
{
public:
    DamageableObject(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth, double hitPoints);
    virtual ~DamageableObject();
    // accessor
    double getHitPt() const;
    // mutators
    void setHitPt(double amt); // Set the hit points to be amt
    virtual void incHitPt(double amt); // Increase the actor's hit points by amt
    virtual void sufferDamage(double amt, int cause); // Decrease the actor's hit points by amt
    
private:
    double m_hitPt;
};

///////////////////
// NachenBlaster //
///////////////////

class NachenBlaster: public DamageableObject
{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    // accessors
    virtual bool isNachenBlaster() const;
    int getCabbagePt() const;
    int getTorpedoPt() const;
    int cabbagePercentage() const;
    int healthPercentage() const;
    // mutators
    void setCabbagePt(int newCabbagePt);
    void incTorpedoPt(int newTorpedoPt);
    virtual void incHitPt(double amt); // Increase this actor's hit points by amt.
    virtual void sufferDamage(double amt, int cause);
    virtual void doSomething();

private:
    int m_cabbagePt;
    int m_torpedoPt;
};

///////////
// Alien //
///////////

class Alien: public DamageableObject
{
public:
    Alien(StudentWorld* World, int imageID, double startX, double startY, double hitPoint, double damageAmt, double deltaX, double deltaY, double speed, unsigned int scoreValue);
    virtual ~Alien();
    // accessors
    virtual bool isAlien() const;
    double getDamageAmt() const;
    double getDeltaY() const;
    double getScoreValue() const;
    double getSpeed() const;
    // mutators
    void setDeltaY(double dy); // Set the player's y direction.
    void setFlightPlanLength(double fpLength);
    void setSpeed(double speed);
    void alienIsDying();
    void move();
    virtual bool damageCollidingPlayer();
    virtual void sufferDamage(double amt, int cause);
    virtual void possiblyDropGoodie();
    virtual void doSomething();
    
private:
    // private pure virtual function
    virtual void doDiffAlienThing() = 0;
    double m_damageAmt;
    double m_deltaY;
    double m_flightPlanLength;
    double m_speed;
    unsigned int m_scoreValue;
};

//////////////
// Smallgon //
//////////////

class Smallgon: public Alien
{
public:
    Smallgon(StudentWorld* World, double startX, double startY);
    virtual ~Smallgon();
    
private:
    virtual void doDiffAlienThing();
};

//////////////
// Smoregon //
//////////////

class Smoregon: public Alien
{
public:
    Smoregon(StudentWorld* World, double startX, double startY);
    virtual ~Smoregon();
    // accessor
    virtual bool isSmoregon() const;
    
private:
    virtual void doDiffAlienThing();
};

////////////////
// Snagglegon //
////////////////

class Snagglegon: public Alien
{
public:
    Snagglegon(StudentWorld* World, double startX, double startY);
    virtual ~Snagglegon();
    // accessor
    virtual bool isSnagglegon() const;
    
private:
    virtual void doDiffAlienThing();
};

////////////////
// Projectile //
////////////////

class Projectile: public Actor
{
public:
    Projectile(StudentWorld* World, int imageID, double startX, double startY, int dir, double damageAmt, double deltaX, bool rotates);
    virtual ~Projectile();
    // accessors
    bool isProjectile() const;
    double getDeltaX() const;
    double getDamageAmt() const;
    virtual bool isFiredByNachenBlaster() const;
    // mutators
    void doCommonThingOnce();
    virtual void doSomething();

private:
    double m_damageAmt;
    double m_deltaX;
    bool m_rotates;
};

/////////////
// Cabbage //
/////////////

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld* World, double startX, double startY);
    virtual ~Cabbage();
    // accessor
    virtual bool isFiredByNachenBlaster() const;
};

////////////
// Turnip //
////////////

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld* World, double startX, double startY);
    virtual ~Turnip();
};

/////////////
// Torpedo //
/////////////

class Torpedo: public Projectile
{
public:
    Torpedo(StudentWorld* World, double startX, double startY, int dir, double deltaX);
    virtual ~Torpedo();
    // accessor
    virtual bool isTorpedo() const;
};

///////////////////////////
// PlayerLaunchedTorpedo //
///////////////////////////

class PlayerLaunchedTorpedo : public Torpedo
{
public:
    PlayerLaunchedTorpedo(StudentWorld* World, double startX, double startY);
    // accessor
    virtual bool isFiredByNachenBlaster() const;
};

//////////////////////////
// AlienLaunchedTorpedo //
//////////////////////////

class AlienLaunchedTorpedo : public Torpedo
{
public:
    AlienLaunchedTorpedo(StudentWorld* World, double startX, double startY);
};

////////////
// Goodie //
////////////

class Goodie: public Actor
{
public:
    Goodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~Goodie();
    // mutators
    bool processCollision();
    virtual void doSomething();
    
private:
    // private pure virtual function
    virtual void doDiffGoodieThing() = 0;
    NachenBlaster* m_NachenBlaster;
};

///////////////////////
// Extra Life Goodie //
///////////////////////

class ELGoodie: public Goodie // extra life goodies
{
public:
    ELGoodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~ELGoodie();
    
private:
    virtual void doDiffGoodieThing();
};

///////////////////
// Repair Goodie //
///////////////////

class RGoodie: public Goodie // repair goodies
{
public:
    RGoodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~RGoodie();
    
private:
    virtual void doDiffGoodieThing();
};

////////////////////
// Torpedo Goodie //
////////////////////

class FTGoodie: public Goodie // flatulence torpedo goodies
{
public:
    FTGoodie(StudentWorld* World, int imageID, double startX, double startY);
    virtual ~FTGoodie();
    
private:
    virtual void doDiffGoodieThing();
};

#endif // ACTOR_H_
