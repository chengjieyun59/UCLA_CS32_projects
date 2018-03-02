#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// TODO: replace the hard code of the damageAmt of the projectile (8.0 and 2.0)
// TODO: when NachenBlaster hit the alien ship, make an explosion
// TODO: when NachenBlaster hit a goodie, why was a life lost?

Actor::Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_isAlive(true), m_world(World), m_createWhat("nothing")
{}

Actor::~Actor()
{}

bool Actor::isInBound(int x, int y) const
{
    if (x < VIEW_WIDTH && x >= 0)
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
    if (isInBound(getX(), getY()) == false)
        setAlive("dead");
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
    moveTo(getX()-1, getY());
}

DamageableObject::DamageableObject(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth, double hitPoints)
:Actor(world, imageID, startX, startY, dir, size, depth), m_hitPt(hitPoints)
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
                    if(getCabbagePt() >= 5)
                    {
                        // Method 1: used this before, but there was a lot of code in void StudentWorld::addActor(Actor* a)
                        // setCreate("cabbage");
                        
                        // method 2:
                        Cabbage *a = new Cabbage(getWorld(), getX()+12, getY());
                        getWorld()->addActor(a);
                        getWorld()->playSound(SOUND_PLAYER_SHOOT);
                        setCabbagePt(getCabbagePt() - 5);
                    } break;
                case KEY_PRESS_TAB:
                    if(getTorpedoPt() > 0)
                    {
                        PlayerLaunchedTorpedo* a = new PlayerLaunchedTorpedo(getWorld(), getX()+12, getY());
                        getWorld()->addActor(a);
                        getWorld()->playSound(SOUND_TORPEDO);
                        setTorpedoPt(getTorpedoPt() - 1);
                    } break;
                case KEY_PRESS_LEFT:   if(isInBound(x-6, y)) moveTo(x-6, y); break;
                case KEY_PRESS_RIGHT:  if(isInBound(x+6, y)) moveTo(x+6, y); break;
                case KEY_PRESS_DOWN:   if(isInBound(x, y-6) && y-6 < VIEW_HEIGHT && y-6 >= 0) moveTo(x, y-6); break;
                case KEY_PRESS_UP:     if(isInBound(x, y+6) && y+6 < VIEW_HEIGHT && y+6 >= 0) moveTo(x, y+6); break;
                default: break;
            }
        }
        processCollision();
    }
    if (getCabbagePt() < 30)
        setCabbagePt(getCabbagePt() + 1);
}

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

void NachenBlaster::sufferDamage(double amt, int cause)
{
    if (cause == HIT_BY_SHIP)
        getWorld()->playSound(SOUND_DEATH);
    else
        getWorld()->playSound(SOUND_BLAST);
    incHitPt(-amt);
    if(getHitPt() <= 0)
        setAlive("dead"); // instead of getWorld()->decLives();
}

void NachenBlaster::setCabbagePt(int newCabbagePt){m_cabbagePt = newCabbagePt;}
int NachenBlaster::getCabbagePt() const {return m_cabbagePt;}
void NachenBlaster::setTorpedoPt(int newTorpedoPt){m_torpedoPt = newTorpedoPt;}
int NachenBlaster::getTorpedoPt() const {return m_torpedoPt;}

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
:DamageableObject(World, imageID, startX, startY, 0, 1.5, 1, hitPoint), m_deltaY(deltaY), m_speed(speed), m_flightPlanLength(0), m_scoreValue(scoreValue)
{}

Alien::~Alien()
{}

bool Alien::isAlien() const {return true;}
void Alien::setDeltaY(double dy) {m_deltaY = dy;} // Set the player's y direction.
double Alien::getDeltaY() const {return m_deltaY;}
void Alien::setSpeed(double speed) {m_speed = speed;} // Set the player's speed.
double Alien::getSpeed() const {return m_speed;}
void Alien::setFlightPlanLength(double fpLength) {m_flightPlanLength = fpLength;}

void Alien::doSomething()
{
    if(isAlive() == false)
        return;
    
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
    move();
    m_flightPlanLength--;
    
    damageCollidingPlayer(m_damageAmt);

    if (getWorld()->getNachenBlaster()->getX() < getX() && getWorld()->getNachenBlaster()->getY()-4 <= getY() && getWorld()->getNachenBlaster()->getY()+4 >= getY())
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
    
    damageCollidingPlayer(m_damageAmt);
}

void Alien::sufferDamage(double amt, int cause)
{
    if(cause == HIT_BY_PROJECTILE)
        incHitPt(-amt);

    if(damageCollidingPlayer(m_damageAmt) == true) // means the alien collides with the nachenblaster
    {
        setAlive("dead");
        getWorld()->recordAlienDestroyed();
        getWorld()->increaseScore(m_scoreValue);
        getWorld()->playSound(SOUND_DEATH);
        Explosion* e = new Explosion(getWorld(), getX(), getY(), 1.0);
        getWorld()->addActor(e);
    }
}

void Alien::move()
{
    moveTo(getX() - 1.0 * m_speed, getY() + m_deltaY * m_speed);
} // Move the player by the current speed in the direction indicated by the x and y deltas.

bool Alien::damageCollidingPlayer(double amt)
{
    NachenBlaster* n = getWorld()->getCollidingPlayer(this);
    
    if(n != nullptr) // means the alien collides with the nachenblaster
    {
        n->sufferDamage(m_damageAmt, 0);
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

void Projectile::doCommonThingOnce()
{
    // vector<Actor*>* m_vActor = getWorld()->getActorVector(); // Don't need this anymore
    if(isFiredByNachenBlaster())
    {
        Alien* a = getWorld()->getOneCollidingAlien(this);
        if(a != nullptr) // means the projectile collides with an alien
        {
            if(isTorpedo())
                a->sufferDamage(8.0, 1);
            else
                a->sufferDamage(2.0, 1);
            if(a->getHitPt() <= 0)
            {
                // if the alien dies, increase the player's score
                if(a->isSnagglegon())
                    getWorld()->increaseScore(1000);
                else
                    getWorld()->increaseScore(250);
                
                a->setAlive("dead");
                getWorld()->recordAlienDestroyed();
                getWorld()->playSound(SOUND_DEATH);
                Explosion* e = new Explosion(getWorld(), a->getX(), a->getY(), 1.0);
                getWorld()->addActor(e); // Introduce a new explosion object into the space field at the same x,y location as the Smallgon.
                a->possiblyDropGoodie();
            }
            else
                getWorld()->playSound(SOUND_BLAST);
            setAlive("dead");
            return;
        }
    }
    
    else //is fired by an alien
    {
        NachenBlaster* n = getWorld()->getCollidingPlayer(this);
        
        if(n != nullptr) // means the projectile collides with the nachenblaster
        {
            if(isTorpedo())
                n->sufferDamage(8.0, 1);
            else
                n->sufferDamage(2.0, 1);
            getWorld()->playSound(SOUND_BLAST);
            setAlive("dead");
            return;
        }
    }
}

void Projectile::doSomething()
{
    if(isAlive() == false)
        return;
    
    doCommonThingOnce();
    doDiffProjectileThing();
    doCommonThingOnce();
}

Cabbage::Cabbage(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_CABBAGE, startX, startY, 0, 2.0, 0.0, false)
// Projectile(World, IID_CABBAGE, startX, startY, 0, damageAmt, deltaX, rotates)
{}

Cabbage::~Cabbage(){}

bool Cabbage::isFiredByNachenBlaster() const {return true;}

void Cabbage::doDiffProjectileThing()
{
    moveTo(getX()+8, getY());
    setDirection(getDirection()+20);
    // TODO: Check if this is counter-clockwise
}

Turnip::Turnip(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_TURNIP, startX, startY, 0, 2.0, 0.0, false)
{}

Turnip::~Turnip()
{}

void Turnip::doDiffProjectileThing()
{
    moveTo(getX()-6, getY());
    setDirection(getDirection()+20); // TODO: Check if this is counter-clockwise
}

Torpedo::Torpedo(StudentWorld* World, double startX, double startY, int dir, double deltaX)
:Projectile(World, IID_TORPEDO, startX, startY, 0, 8.0, 0.0, true)
{}

Torpedo::~Torpedo()
{}

void Torpedo::doDiffProjectileThing()
{}

bool Torpedo::isTorpedo() const {return true;}

PlayerLaunchedTorpedo::PlayerLaunchedTorpedo(StudentWorld* World, double startX, double startY)
:Torpedo(World, startX, startY, 0, 0)
{}

bool PlayerLaunchedTorpedo::isFiredByNachenBlaster() const {return false;}

void PlayerLaunchedTorpedo::doDiffProjectileThing()
{
    moveTo(getX()+8, getY());
}

AlienLaunchedTorpedo::AlienLaunchedTorpedo(StudentWorld* World, double startX, double startY)
:Torpedo(World, startX, startY, 180, 0)
{}

void AlienLaunchedTorpedo::doDiffProjectileThing()
{
    moveTo(getX()-8, getY());
}

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
    processCollision();
    moveTo(getX()-0.75, getY()-0.75);
    processCollision();
}

void Goodie::processCollision()
{
    NachenBlaster* n = getWorld()->getCollidingPlayer(this);

    if(n != nullptr) // means the goodie collides with the nachenblaster
    {
        getWorld()->increaseScore(100); // TODO: this if statement is never entered
        setAlive("dead");
        getWorld()->playSound(SOUND_GOODIE);
        doDiffGoodieThing();
        return;
    }
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
    if(getWorld()->getNachenBlaster()->getHitPt() <= 40)
        getWorld()->getNachenBlaster()->incHitPt(10);
    else
        getWorld()->getNachenBlaster()->incHitPt(getWorld()->getNachenBlaster()->getHitPt() - getWorld()->getNachenBlaster()->getHitPt() + 50);
} // Inform the NachenBlaster object that it just got 10 additional hit points (any additional hit points must NOT cause the NachenBlaster to exceed 50 hit points).

FTGoodie::FTGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_TORPEDO_GOODIE, startX, startY)
{}

FTGoodie::~FTGoodie()
{}

void FTGoodie::doDiffGoodieThing()
{
    getWorld()->getNachenBlaster()->setTorpedoPt(getWorld()->getNachenBlaster()->getTorpedoPt() + 5);
}     // Inform the NachenBlaster object that it just received 5 Flatulence Torpedoes
