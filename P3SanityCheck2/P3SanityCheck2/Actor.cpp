#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// TODO: replace the hard code of the damageAmt of the projectile (8.0 and 2.0)
// TODO: when NachenBlaster hit the alien ship, make an explosion
// TODO: when NachenBlaster hit a goodie, why was a life lost?

Actor::Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_isAlive(true), m_world(World)
{}

Actor::~Actor()
{}

bool Actor::isInBound(int x, int y) const
{
    if (x < VIEW_WIDTH && x >= 0 && y >= 0 && y < VIEW_HEIGHT)
        return true;
    return false;
}

void Actor::setAlive(string aliveStatus)
{
    if(aliveStatus == "dead")
        m_isAlive = false;
    else
        m_isAlive = true;
}

bool Actor::isAlive()
{
    return m_isAlive;
}

bool Actor::isAlien() const {return false;}
bool Actor::isProjectile() const {return false;}
bool Actor::isNachenBlaster() const {return false;}
bool Actor::isStar() const {return false;}
bool Actor::isTorpedo() const {return false;}
bool Actor::isSmoregon() const {return false;}
bool Actor::isSnagglegon() const {return false;}

StudentWorld* Actor::getWorld() const
{
    return m_world;
} // a method in one of its base classes that returns a pointer to a StudentWorld), and then uses this pointer to call any methods in StudentWorld.cpp

Star::Star(StudentWorld* World, double startX)
:Actor(World, IID_STAR, startX, randInt(0, VIEW_HEIGHT-1), 0, randInt(5, 50)/100.0, 3)
{}

Star::~Star()
{}

bool Star::isStar() const {return true;}

void Star::doSomething()
{
    if(getX() < 0)
    {
        setAlive("dead");
        return;
    }
    moveTo(getX()-1, getY());
}

DamageableObject::DamageableObject(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth, double hitPoints)
:Actor(world, imageID, startX, startY, dir, size, depth), m_hitPt(hitPoints)
{}

DamageableObject::~DamageableObject()
{}

double DamageableObject::getHitPt() const {return m_hitPt;}
void DamageableObject::incHitPt(double amt) {m_hitPt = m_hitPt + amt;} // Increase this actor's hit points by amt.

void DamageableObject::sufferDamage(double amt, int cause)
{
    m_hitPt = m_hitPt - amt; // TODO: const int HIT_BY_SHIP = 0; & const int HIT_BY_PROJECTILE = 1;
} // This actor suffers an amount of damage caused by being hit by either a ship or a projectile (see constants above).

NachenBlaster::NachenBlaster(StudentWorld* World)
:DamageableObject(World, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, 50), m_cabbagePt(30), m_torpedoPt(0)
{}

NachenBlaster::~NachenBlaster()
{}

bool NachenBlaster::isNachenBlaster() const {return true;}

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
            switch (value)
            {
                    
                case KEY_PRESS_SPACE:
                    if(m_cabbagePt >= 5)
                    {
                        // Method 1: used this before, but there was a lot of code in void StudentWorld::addActor(Actor* a)
                        // setCreate("cabbage");
                        
                        // method 2:
                        Cabbage *a = new Cabbage(getWorld(), getX()+12, getY());
                        getWorld()->addActor(a);
                        getWorld()->playSound(SOUND_PLAYER_SHOOT);
                        m_cabbagePt -= 5;
                    } break;
                    
                case KEY_PRESS_TAB:
                    if(m_torpedoPt > 0)
                    {
                        PlayerLaunchedTorpedo* a = new PlayerLaunchedTorpedo(getWorld(), getX()+12, getY());
                        getWorld()->addActor(a);
                        getWorld()->playSound(SOUND_TORPEDO);
                        m_torpedoPt--;
                    } break;
                    
                case KEY_PRESS_LEFT:   if(isInBound(x-6, y)) moveTo(x-6, y); break;
                case KEY_PRESS_RIGHT:  if(isInBound(x+6, y)) moveTo(x+6, y); break;
                case KEY_PRESS_DOWN:   if(isInBound(x, y-6)) moveTo(x, y-6); break;
                case KEY_PRESS_UP:     if(isInBound(x, y+6)) moveTo(x, y+6); break;
                default:
                    break;
            }
        }
        // processCollision();
    }
    if (m_cabbagePt < 30)
        m_cabbagePt++;
}

/*
 void NachenBlaster::processCollision()
 {
 vector<Actor*>* m_vActor = getWorld()->getActorVector();
 
 for(auto a = (*m_vActor).begin(); a != (*m_vActor).end(); a++) // put a star to de-reference the m_vActor pointer
 {
 if((*a)->isNachenBlaster() || (*a)->isStar())
 continue;
 
 NachenBlaster* n = getWorld()->getCollidingPlayer(*a);
 
 if (n != nullptr) {
 if((*a)->isAlien())
 {
 getWorld()->recordAlienDestroyed();
 if(!(*a)->isSnagglegon())
 sufferDamage(5, 0); // collide with a smallgon or snoregon
 else
 sufferDamage(15, 0); // collide with a snagglegon
 Explosion* e = new Explosion(getWorld(), getX(), getY(), 1.0);
 getWorld()->addActor(e); // TODO: Why wasn't any explosion created?
 }
 else if((*a)->isProjectile())
 {
 if((*a)->isTorpedo())
 sufferDamage(8, 1); // collide with a torpedo
 else
 sufferDamage(2, 1); // collide with a turnip or cabbage
 }
 (*a)->setAlive("dead");
 }
 }
 }
 */

void NachenBlaster::sufferDamage(double amt, int cause)
{
    if (cause == HIT_BY_PROJECTILE)
        getWorld()->playSound(SOUND_BLAST);
    incHitPt(-amt);
    if(getHitPt() <= 0)
        setAlive("dead");
}

void NachenBlaster::setCabbagePt(int newCabbagePt){m_cabbagePt = newCabbagePt;}
int NachenBlaster::getCabbagePt() const {return m_cabbagePt;}
void NachenBlaster::incTorpedoPt(int newTorpedoPt){m_torpedoPt += newTorpedoPt;}
int NachenBlaster::getTorpedoPt() const {return m_torpedoPt;}
int NachenBlaster::cabbagePercentage() const {return (m_cabbagePt*100/30);}
int NachenBlaster::healthPercentage() const {return (getHitPt()*100/50);}

// maximum hit point is only 50
void NachenBlaster::incHitPt(double amt)
{
    if(getHitPt() + amt <= 50)
        DamageableObject::incHitPt(amt);
    else
        DamageableObject::incHitPt(getHitPt()-getHitPt()+50);
}

Explosion::Explosion(StudentWorld* World, double startX, double startY, double size)
:Actor(World, IID_EXPLOSION, startX, startY, 0, 1.0, 0)
{}

Explosion::~Explosion()
{}

void Explosion::doSomething()
{
    // First four powers of 1.5: 1.5, 2.25, 3.375, 5.0625
    if (getSize() < 6.0)
        setSize(1.5 * getSize());
    if (getSize() == 5.0625)
        setAlive("dead");
}

///////////
// Alien //
///////////

Alien::Alien(StudentWorld* World, int imageID, double startX, double startY, double hitPoint, double damageAmt, double deltaX, double deltaY, double speed, unsigned int scoreValue)
:DamageableObject(World, imageID, startX, startY, 0, 1.5, 1, hitPoint), m_deltaY(deltaY), m_speed(speed), m_flightPlanLength(0), m_scoreValue(scoreValue), m_damageAmt(damageAmt)
{}

Alien::~Alien()
{}

bool Alien::isAlien() const {return true;}
void Alien::setDeltaY(double dy) {m_deltaY = dy;} // Set the player's y direction.
double Alien::getDeltaY() const {return m_deltaY;}
double Alien::getDamageAmt() const {return m_damageAmt;}
double Alien::getScoreValue() const {return m_scoreValue;}
void Alien::setSpeed(double speed) {m_speed = speed;} // Set the player's speed.
double Alien::getSpeed() const {return m_speed;}
void Alien::setFlightPlanLength(double fpLength) {m_flightPlanLength = fpLength;}

void Alien::doSomething()
{
    if(isAlive() == false)
        return;
    
    if(getX() < 0)
    {
        setAlive("dead");
        return;
    }
    
    if(damageCollidingPlayer())
        sufferDamage(-1.0, HIT_BY_SHIP);
    
    if(getY() >= VIEW_HEIGHT-1 || getY() <= 0 || m_flightPlanLength == 0)
    {
        if(getY() >= VIEW_HEIGHT-1)
            setDeltaY(-1.0); // hit top, go down
        else if (getY() <= 0)
            setDeltaY(1.0); // hit bottom, go up
        else if (!isSnagglegon() && m_flightPlanLength == 0)
            setDeltaY(randInt(-1, 1)); // with 1/3 change each, go up, down, or directly left
        if(!isSnagglegon())
            m_flightPlanLength = randInt(1, 32);
    }
    
    if(damageCollidingPlayer())
        sufferDamage(-1.0, HIT_BY_SHIP);
    
    if (getWorld()->playerInLineOfFire(this))
    {
        if(!isSnagglegon() && randInt(1, (20/getWorld()->getLevel())+5) == 1)
        {
            Turnip* t = new Turnip(getWorld(), getX()-14, getY());
            getWorld()->addActor(t);
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
            return;
        }
        doDiffAlienThing();
    }
    move();
    m_flightPlanLength--;
    
    if(damageCollidingPlayer())
        sufferDamage(-1.0, HIT_BY_SHIP);
}

void Alien::sufferDamage(double amt, int cause)
{
    if(cause == HIT_BY_PROJECTILE)
    {
        incHitPt(-amt);
        if(getHitPt() <= 0)
        {
            // alien died
            getWorld()->playSound(SOUND_DEATH);
            setAlive("dead");
            getWorld()->recordAlienDestroyed();
            getWorld()->increaseScore(getScoreValue());
            Explosion* e = new Explosion(getWorld(), getX(), getY(), 1.0);
            getWorld()->addActor(e);
            possiblyDropGoodie();
        }
        else
            getWorld()->playSound(SOUND_BLAST);
    }
    
    if(cause == HIT_BY_SHIP) // means the alien collides with the nachenblaster
    {
        // alien died
        getWorld()->playSound(SOUND_DEATH);
        setAlive("dead");
        getWorld()->recordAlienDestroyed();
        getWorld()->increaseScore(getScoreValue());
        Explosion* e = new Explosion(getWorld(), getX(), getY(), 1.0);
        getWorld()->addActor(e);
        possiblyDropGoodie();
    }
}

void Alien::move()
{
    moveTo(getX() - 1.0 * m_speed, getY() + m_deltaY * m_speed);
} // Move the player by the current speed in the direction indicated by the x and y deltas.

bool Alien::damageCollidingPlayer()
{
    NachenBlaster* n = getWorld()->getCollidingPlayer(this);
    
    if(n != nullptr) // means the alien collides with the nachenblaster
    {
        // Explosion* e = new Explosion(getWorld(), getX(), getY(), 1.0);
        // getWorld()->addActor(e); // explosion here is only of size 1
        n->sufferDamage(getDamageAmt(), HIT_BY_SHIP);
        return true;
    }
    return false;
} // If this alien collided with the player, damage the player and return true; otherwise, return false.

void Alien::possiblyDropGoodie()
{
    // There is a 50% chance that a Smoregon will be a Repair Goodie, and a 50% chance that it will be a Flatulence Torpedo Goodie. The goodie must be added to the space field at the same x,y coordinates as the destroyed ship.
    if(isSmoregon() && randInt(1, 3) == 1) //1/3
    {
        if(randInt(1, 2) == 1)// 1/2
        {
            RGoodie* a = new RGoodie(getWorld(), IID_REPAIR_GOODIE, getX(), getY());
            getWorld()->addActor(a);
        }
        else
        {
            FTGoodie* a = new FTGoodie(getWorld(), IID_TORPEDO_GOODIE, getX(), getY());
            getWorld()->addActor(a);
        }
    }
    
    // There is a 1/6 chance that the destroyed Snagglegon ship will drop an Extra Life goodie. The goodie must be added to the space field at the same x,y coordinates as the destroyed ship.
    if(isSnagglegon() && randInt(1, 6) == 1) //1/6
    {
        ELGoodie* a = new ELGoodie(getWorld(), IID_LIFE_GOODIE, getX(), getY());
        getWorld()->addActor(a);
    }
} // If this alien drops goodies, drop one with the appropriate probability.

//////////////
// Smallgon //
//////////////

Smallgon::Smallgon(StudentWorld* World, double startX, double startY)
:Alien(World, IID_SMALLGON, startX, startY, 0.0, 5.0, -1.0, 0.0, 2.0, 250)
//Alien(World, IID_SMALLGON, startX, startY, (5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), damageAmt, deltaX, deltaY, 2.0, scoreValue)
{
    incHitPt(5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1));
}

Smallgon::~Smallgon()
{}

void Smallgon::doDiffAlienThing()
{}

//////////////
// Smoregon //
//////////////

Smoregon::Smoregon(StudentWorld* World, double startX, double startY)
:Alien(World, IID_SMOREGON, startX, startY, 0.0, 5.0, -1.0, 0.0, 2.0, 250)
{
    incHitPt(5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1));
}

Smoregon::~Smoregon()
{}

bool Smoregon::isSmoregon() const {return true;}

void Smoregon::doDiffAlienThing()
{
    if(randInt(1, (20/getWorld()->getLevel())+5) == 1)
    {
        setDeltaY(0.0);
        setFlightPlanLength(VIEW_WIDTH);
        setSpeed(5.0);
    }
}

////////////////
// Snagglegon //
////////////////

Snagglegon::Snagglegon(StudentWorld* World, double startX, double startY)
:Alien(World, IID_SNAGGLEGON, startX, startY, 0.0, 15.0, -1.0, -1.0, 1.75, 1000)
{
    incHitPt(10.0*(1.0+(getWorld()->getLevel()-1.0)*0.1));
}

Snagglegon::~Snagglegon()
{}

bool Snagglegon::isSnagglegon() const {return true;}

void Snagglegon::doDiffAlienThing()
{
    // Fire a Torpedo toward the NachenBlaster
    if(randInt(1, (15/getWorld()->getLevel())+10) == 1)
    {
        AlienLaunchedTorpedo* a = new AlienLaunchedTorpedo(getWorld(), getX()-14, getY());
        getWorld()->addActor(a);
        getWorld()->playSound(SOUND_TORPEDO);
        return;
    }
}

////////////////
// Projectile //
////////////////

Projectile::Projectile(StudentWorld* World, int imageID, double startX, double startY, int dir, double damageAmt, double deltaX, bool rotates)
:Actor(World, imageID, startX, startY, dir, 0.5, 1), m_damageAmt(damageAmt), m_deltaX(deltaX), m_rotates(rotates)
{}

Projectile::~Projectile()
{}

bool Projectile::isFiredByNachenBlaster() const {return false;}
bool Projectile::isProjectile() const {return true;}
double Projectile::getDeltaX() const {return m_deltaX;}
double Projectile::getDamageAmt() const {return m_damageAmt;}

void Projectile::doCommonThingOnce()
{
    // vector<Actor*>* m_vActor = getWorld()->getActorVector(); // Don't need this anymore
    if(isFiredByNachenBlaster())
    {
        Alien* a = getWorld()->getOneCollidingAlien(this);
        if(a != nullptr) // means the projectile collides with an alien
        {
            a->sufferDamage(getDamageAmt(), HIT_BY_PROJECTILE);
            setAlive("dead");
            return;
        }
    }
    
    else //is fired by an alien
    {
        NachenBlaster* n = getWorld()->getCollidingPlayer(this);
        if(n != nullptr) // means the projectile collides with the nachenblaster
        {
            n->sufferDamage(getDamageAmt(), HIT_BY_PROJECTILE);
            setAlive("dead");
            return;
        }
    }
} // handle the cases when the projectile collides with either the nachenblaster or alien

void Projectile::doSomething()
{
    if(isAlive() == false)
        return;
    
    if(isInBound(getX(), getY()) == false)
    {
        setAlive("dead");
        return;
    }
    
    doCommonThingOnce();
    moveTo(getX()+getDeltaX(), getY());
    if(m_rotates == true)
        setDirection(getDirection()+20);
    doCommonThingOnce();
}

Cabbage::Cabbage(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_CABBAGE, startX, startY, 0, 2.0, 8.0, true)
// Projectile(World, IID_CABBAGE, startX, startY, 0, damageAmt, deltaX, rotates)
{}

Cabbage::~Cabbage(){}

bool Cabbage::isFiredByNachenBlaster() const {return true;}

Turnip::Turnip(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_TURNIP, startX, startY, 0, 2.0, -6.0, true)
{}

Turnip::~Turnip()
{}

Torpedo::Torpedo(StudentWorld* World, double startX, double startY, int dir, double deltaX)
:Projectile(World, IID_TORPEDO, startX, startY, 0, 8.0, deltaX, false)
{}

Torpedo::~Torpedo()
{}

bool Torpedo::isTorpedo() const {return true;}

PlayerLaunchedTorpedo::PlayerLaunchedTorpedo(StudentWorld* World, double startX, double startY)
:Torpedo(World, startX, startY, 0, 8.0)
{}

bool PlayerLaunchedTorpedo::isFiredByNachenBlaster() const {return true;}

AlienLaunchedTorpedo::AlienLaunchedTorpedo(StudentWorld* World, double startX, double startY)
:Torpedo(World, startX, startY, 180, -8.0)
{}

////////////
// Goodie //
////////////

Goodie::Goodie(StudentWorld* World, int imageID, double startX, double startY)
:Actor(World, imageID, startX, startY, 0, 0.5, 1)
{}

Goodie::~Goodie()
{}

void Goodie::doSomething()
{
    if(isAlive() == false)
        return;
    if(isInBound(getX(), getY()) == false)
    {
        setAlive("dead");
        return;
    }
    if(processCollision() == true)
    {
        setAlive("dead");
        return;
    }
    moveTo(getX()-0.75, getY()-0.75);
    if(processCollision() == true)
    {
        setAlive("dead");
        return;
    }
}

bool Goodie::processCollision()
{
    NachenBlaster* n = getWorld()->getCollidingPlayer(this);
    
    if(n != nullptr) // means the goodie collides with the nachenblaster
    {
        getWorld()->increaseScore(100); // TODO: this if statement is never entered
        // setAlive("dead"); // set later
        getWorld()->playSound(SOUND_GOODIE);
        doDiffGoodieThing();
        return true;
    }
    return false;
}

ELGoodie::ELGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_LIFE_GOODIE, startX, startY)
{}

ELGoodie::~ELGoodie()
{}

void ELGoodie::doDiffGoodieThing()
{
    getWorld()->incLives(); // NachenBlaster gains one extra life.
}

RGoodie::RGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_REPAIR_GOODIE, startX, startY)
{}

RGoodie::~RGoodie()
{}

void RGoodie::doDiffGoodieThing()
{
    getWorld()->getNachenBlaster()->incHitPt(10);
} // Inform the NachenBlaster object that it just got 10 additional hit points (any additional hit points must NOT cause the NachenBlaster to exceed 50 hit points).

FTGoodie::FTGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_TORPEDO_GOODIE, startX, startY)
{}

FTGoodie::~FTGoodie()
{}

void FTGoodie::doDiffGoodieThing()
{
    getWorld()->getNachenBlaster()->incTorpedoPt(5);
}     // Inform the NachenBlaster object that it just received 5 Flatulence Torpedoes


