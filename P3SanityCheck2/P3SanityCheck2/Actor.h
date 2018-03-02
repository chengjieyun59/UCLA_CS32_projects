#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
using namespace std;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Actor();
    virtual void doSomething() = 0; // move around, cause damage, grant bonuses, etc.
    bool isInBound(int x, int y) const;
    bool isAlive();
    virtual bool isAlien() const;
    virtual bool isProjectile() const;
    virtual bool isStar() const;
    virtual bool isNachenBlaster() const;
    virtual bool isTorpedo() const;
    virtual bool isSmoregon() const;
    virtual bool isSnagglegon() const;
    virtual void setAlive(std::string aliveStatus);
    StudentWorld* getWorld() const;
    
private:
    bool m_isAlive;
    StudentWorld* m_world;
}; // Each actor has its own x,y location in space, its own internal state (e.g., a Snagglegon knows its location, what direction it’s moving, etc.) and its own special algorithms that control its actions in the game based on its own state and the state of the other objects in the world.

class Star: public Actor
{
public:
    Star(StudentWorld* World, double startX);
    virtual ~Star();
    virtual void doSomething();
    virtual bool isStar() const;
};

class Explosion: public Actor
{
public:
    Explosion(StudentWorld* World, double startX, double startY, double size);
    virtual ~Explosion();
    virtual void doSomething();
};

class DamageableObject: public Actor
{
public:
    DamageableObject(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth, double hitPoints);
    virtual ~DamageableObject();
    double getHitPt() const;
    void setHitPt(double amt); // Set the hit points to be amt
    virtual void incHitPt(double amt); // Increase this actor's hit points by amt.
    virtual void sufferDamage(double amt, int cause); // This actor suffers an amount of damage caused by being hit by either a ship or a projectile (see constants above).
    
private:
    double m_hitPt;
};

class NachenBlaster: public DamageableObject
{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual void doSomething();
    virtual void sufferDamage(double amt, int cause);
    // void processCollision();
    virtual bool isNachenBlaster() const;
    
    void setCabbagePt(int newCabbagePt);
    int getCabbagePt() const;
    void incTorpedoPt(int newTorpedoPt);
    int getTorpedoPt() const;
    int cabbagePercentage() const;
    int healthPercentage() const;
    virtual void incHitPt(double amt); // Increase this actor's hit points by amt.
    
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
    
    virtual bool isAlien() const;
    void setDeltaY(double dy); // Set the player's y direction.
    double getDeltaY() const;
    void setSpeed(double speed);
    double getSpeed() const;
    void setFlightPlanLength(double fpLength);
    double getDamageAmt() const;
    double getScoreValue() const;
    
    virtual void doSomething();
    virtual void sufferDamage(double amt, int cause);
    void alienIsDying();
    void move();
    virtual bool damageCollidingPlayer();
    virtual void possiblyDropGoodie();
    
private:
    virtual void doDiffAlienThing() = 0;
    double m_flightPlanLength;
    double m_deltaY;
    double m_speed;
    double m_damageAmt;
    unsigned int m_scoreValue;
};

class Smallgon: public Alien
{
public:
    Smallgon(StudentWorld* World, double startX, double startY);
    virtual ~Smallgon();
    
private:
    virtual void doDiffAlienThing();
};

class Smoregon: public Alien
{
public:
    Smoregon(StudentWorld* World, double startX, double startY);
    virtual ~Smoregon();
    virtual bool isSmoregon() const;
    
private:
    virtual void doDiffAlienThing();
};

class Snagglegon: public Alien
{
public:
    Snagglegon(StudentWorld* World, double startX, double startY);
    virtual ~Snagglegon();
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
    bool isProjectile() const;
    virtual bool isFiredByNachenBlaster() const;
    virtual void doSomething();
    void doCommonThingOnce();
    double getDeltaX() const;
    double getDamageAmt() const;
    
private:
    double m_damageAmt;
    double m_deltaX;
    bool m_rotates;
};

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld* World, double startX, double startY);
    virtual ~Cabbage();
    virtual bool isFiredByNachenBlaster() const;
};

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld* World, double startX, double startY);
    virtual ~Turnip();
};

class Torpedo: public Projectile
{
public:
    Torpedo(StudentWorld* World, double startX, double startY, int dir, double deltaX);
    virtual ~Torpedo();
    virtual bool isTorpedo() const;
};

class PlayerLaunchedTorpedo : public Torpedo
{
public:
    PlayerLaunchedTorpedo(StudentWorld* World, double startX, double startY);
    virtual bool isFiredByNachenBlaster() const;
};

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
    virtual void doSomething();
    bool processCollision();
    
private:
    virtual void doDiffGoodieThing() = 0;
    NachenBlaster* m_NachenBlaster;
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

#endif // ACTOR_H_

