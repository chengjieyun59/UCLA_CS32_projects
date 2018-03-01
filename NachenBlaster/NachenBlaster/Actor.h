#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
using namespace std;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;

//class GameWorld;
class StudentWorld;
//class GameController;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth);
    virtual ~Actor();
    virtual void doSomething() = 0; // move around, cause damage, grant bonuses, etc.
    bool isInBound(int x, int y) const;
    bool isAlive();
    virtual bool isAlien() const;
    virtual bool isTorpedo() const;
    virtual bool isSmoregon() const;
    virtual bool isSnagglegon() const;
    virtual void setAlive(std::string aliveStatus);
    void setCreate(string createWhat);
    string getCreate() const;
    StudentWorld* getWorld() const;
    
    // GameController* getControl();
    
    // Move this actor to x,y if onscreen; otherwise, don't move and mark
    // this actor as dead.
    // virtual void moveTo(double x, double y);
    
private:
    bool m_isAlive;
    StudentWorld* m_world;
    string m_createWhat;
    //GameController* m_control;
    
}; // Each actor has its own x,y location in space, its own internal state (e.g., a Snagglegon knows its location, what direction it’s moving, etc.) and its own special algorithms that control its actions in the game based on its own state and the state of the other objects in the world.

class Star: public Actor
{
public:
    Star(StudentWorld* World, double startX);
    virtual ~Star();
    virtual void doSomething();
}; // page 26

class Explosion: public Actor
{
public:
    Explosion(StudentWorld* World, double startX, double startY, double size);
    virtual ~Explosion();
    virtual void doSomething();
    
private:
    
};

class DamageableObject : public Actor
{
public:
    DamageableObject(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth, double hitPoints);
    // How many hit points does this actor have left?
    double getHitPt() const;
    
    // Increase this actor's hit points by amt.
    virtual void incHitPt(double amt);
    
    // This actor suffers an amount of damage caused by being hit by either
    // a ship or a projectile (see constants above).
    virtual void sufferDamage(double amt, int cause);
    
private:
    double m_hitPt;
};

class NachenBlaster: public DamageableObject
{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual void doSomething();
    virtual void incHitPt(double amt);
    virtual void sufferDamage(double amt, int cause);

    void setHealthPt(int newHealthPt);
    int getHealthPt() const;
    
    void setCabbagePt(int newCabbagePt);
    int getCabbagePt() const;
    
    void setTorpedoPt(int newTorpedoPt);
    int getTorpedoPt() const;
    
private:
    int m_healthPt;
    int m_cabbagePt;
    int m_torpedoPt;
}; // the algorithm that controls the ship object is the user’s own brain and hand, and the keyboard
// page 23-25

///////////
// Alien //
///////////

class Alien: public DamageableObject
{
public:
    Alien(StudentWorld* World, int imageID, double startX, double startY, double hitPoint, double damageAmt, double deltaX, double deltaY, double speed, unsigned int scoreValue);
    virtual ~Alien();
    virtual bool isAlien() const;
    virtual void doSomething();
    // Hint: getWorld->zapAllZappableActors(getX(), getY());
    virtual void sufferDamage(double amt, int cause);
    
    // Move the player by the current speed in the direction indicated
    // by the x and y deltas.
    void move();
    void setDeltaY(double dy); // Set the player's y direction.
    double getDeltaY() const;
    void setSpeed(double speed);
    double getSpeed() const;

    // If this alien collided with the player, damage the player and return
    // true; otherwise, return false.
    virtual bool damageCollidingPlayer(double amt);
    
    // If this alien drops goodies, drop one with the appropriate probability.
    virtual void possiblyDropGoodie();
    
private:
    virtual void doDiffAlienThing() = 0;
    double m_damageAmt;
    double m_flightPlanLength;
    double m_deltaY;
    double m_speed;
    unsigned int m_scoreValue;
};

class Smallgon: public Alien
{
public:
    Smallgon(StudentWorld* World, double startX, double startY);
    virtual ~Smallgon();
    virtual void sufferDamage(double amt, int cause);
    
private:
    virtual void doDiffAlienThing();
    
};

class Smoregon: public Alien
{
public:
    Smoregon(StudentWorld* World, double startX, double startY);
    virtual ~Smoregon();
    virtual bool isSmoregon() const;
    virtual void sufferDamage(double amt, int cause);
    
private:
    virtual void doDiffAlienThing();

};

class Snagglegon: public Alien
{
public:
    Snagglegon(StudentWorld* World, double startX, double startY);
    virtual ~Snagglegon();
    virtual bool isSnagglegon() const;
    virtual void sufferDamage(double amt, int cause);
    
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
    virtual void doSomething();
    virtual void attacked();
    
private:
    virtual void doDiffProjectileThing() = 0;
    double m_damageAmt;
    double m_deltaX;
    bool m_rotates;
};

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld* World, double startX, double startY);
    virtual ~Cabbage();
    
private:
    virtual void doDiffProjectileThing();
};

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld* World, double startX, double startY);
    virtual ~Turnip();
    
private:
    virtual void doDiffProjectileThing();
};

class Torpedo: public Projectile
{
public:
    Torpedo(StudentWorld* World, double startX, double startY, int dir, double deltaX);
    virtual ~Torpedo();
    virtual bool isTorpedo() const;
    virtual void doSomething();
    
private:
    
};

class PlayerLaunchedTorpedo : public Torpedo
{
public:
    PlayerLaunchedTorpedo(StudentWorld* World, double startX, double startY);
    virtual void doSomething();
};

class AlienLaunchedTorpedo : public Torpedo
{
public:
    AlienLaunchedTorpedo(StudentWorld* World, double startX, double startY);
    virtual void doSomething();
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
    virtual void attacked();
    
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
