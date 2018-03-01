#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_isAlive(true), m_world(World), m_createWhat("nothing")//, m_control(Control)
{} // page 22

Actor::~Actor()
{
    // delete getWorld(); // wrong!!!! Delete all the memories that only this class made. Or C++ will try to delete it twice. Bad pointer execution
}

bool Actor::isInBound(int x, int y) const
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

bool Actor::isAlien() const {return false;}
bool Actor::isTorpedo() const {return false;}
bool Actor::isSmoregon() const {return false;}
bool Actor::isSnagglegon() const {return false;}
void Actor::setCreate(string createWhat) {m_createWhat = createWhat;}
string Actor::getCreate() const {return m_createWhat;}

StudentWorld* Actor::getWorld() const
{
    return m_world;
} // a method in one of its base classes that returns a pointer to a StudentWorld), and then uses this pointer to call the getKey() method.

/*
GameController* Actor::getControl()
{
    return m_control;
}
*/

Star::Star(StudentWorld* World, double startX)
:Actor(World, IID_STAR, startX, randInt(0, VIEW_HEIGHT-1), 0, randInt(5, 50)/100.0, 3)
{}

Star::~Star()
{} // empty destructor

void Star::doSomething()
{
    moveTo(getX()-1, getY());
}

DamageableObject::DamageableObject(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth, double hitPoints)
:Actor(world, imageID, startX, startY, dir, size, depth), m_hitPt(hitPoints)
{}

// How many hit points does this actor have left?
double DamageableObject::getHitPt() const
{
    return m_hitPt;
}

// Increase this actor's hit points by amt.
void DamageableObject::incHitPt(double amt)
{
    m_hitPt = m_hitPt + amt;
}

// This actor suffers an amount of damage caused by being hit by either
// a ship or a projectile (see constants above).
void DamageableObject::sufferDamage(double amt, int cause)
{
    m_hitPt = m_hitPt - amt;
    // TODO: const int HIT_BY_SHIP = 0; & const int HIT_BY_PROJECTILE = 1;
}

NachenBlaster::NachenBlaster(StudentWorld* World)
 :DamageableObject(World, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, 50), m_cabbagePt(30), m_torpedoPt(0)
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
            switch (value)
            {
                case KEY_PRESS_SPACE:
                    if(getCabbagePt() >= 5)
                    {
                        // method 1?? a lot of code though, in void StudentWorld::addActor(Actor* a)
                        setCreate("cabbage");
                        
                        // method 2? How to make this work
                        Cabbage *c;
                        getWorld()->addActor(c);
                        // TODO Hint: When you create a new cabbage object in the proper location, give it to the StudentWorld to manage (e.g., animate) along with the other game objects.
                        
                        getWorld()->playSound(SOUND_PLAYER_SHOOT);
                        setCabbagePt(getCabbagePt() - 5);
                    } break;
                    
                case KEY_PRESS_TAB:
                    if(getTorpedoPt() > 0)
                    {
                        // TODO:
                        //Torpedo* c = new Torpedo(this, getX()+12, getY(), 0);
                        getWorld()->playSound(SOUND_TORPEDO);
                        setTorpedoPt(getTorpedoPt() - 1);
                    }
                    break;
                    
                case KEY_PRESS_LEFT:   if(isInBound(x-6, y)) moveTo(x-6, y);
                    if (getWorld()->getCollidingPlayer(this) != nullptr) {
                        if(getWorld()->getCollidingPlayer(this)->isAlien())
                        {
                            if(getWorld()->getCollidingPlayer(this)->isSnagglegon())
                                sufferDamage(5, 0); // collide with a smallgon or snoregon
                            else
                                sufferDamage(15, 0); // collide with a snagglegon
                        }

                        else
                        {
                            if(getWorld()->getCollidingPlayer(this)->isTorpedo())
                                sufferDamage(8, 1); // collide with a torpedo
                            else
                                sufferDamage(2, 1); // collide with a turnip or cabbage
                        }
                    } // Of course, any movement may cause a collision with an alien ship or projectile, so you must check for this. TODO: is this correct? If so, add to the other 3 directions
                    break;
                case KEY_PRESS_RIGHT:  if(isInBound(x+6, y)) moveTo(x+6, y);
                    
                    break;
                case KEY_PRESS_DOWN:   if(isInBound(x, y-6)) moveTo(x, y-6);
                    
                    break;
                case KEY_PRESS_UP:     if(isInBound(x, y+6)) moveTo(x, y+6);
                    
                    break;
                    
                    // TODO: case KEY_PRESS_ESCAPE: ; break;
                    
                default:
                    break;
            }
        }
    }
    if (getCabbagePt() < 30)
        setCabbagePt(getCabbagePt() + 1);
}

void NachenBlaster::incHitPt(double amt)
{
    // TODO
}

void NachenBlaster::sufferDamage(double amt, int cause)
{
    /* TODO:
    if (a projectile collides with the NachenBlaster, or vice versa)
    {
        setHitpt(getHitPt() - amt);
        getWorld()->playSound(SOUND_BLAST);
    }

    if (an alien ship collides with the NachenBlaster or vice versa)
        the NachenBlaster incurs damage and the alien ship will be destroyed
     {
        setHitpt(getHitPt() - amt);
        getWorld()->playSound(SOUND_DEATH);
     }
     */
    
    if(getHitPt() <= 0)
        getWorld()->decLives();
}

void NachenBlaster::setHealthPt(int newHealthPt){m_healthPt = newHealthPt;}
int NachenBlaster::getHealthPt() const {return m_healthPt;}

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
    if (getSize() < 6.0)
    {
        setSize(1.5 * getSize());
    } // First four powers of 1.5: 1.5, 2.25, 3.375, 5.0625
    
    if (getSize() == 5.0625)
        setAlive("Dead");
}

///////////
// Alien //
///////////

Alien::Alien(StudentWorld* World, int imageID, double startX, double startY, double hitPoint, double damageAmt, double deltaX, double deltaY, double speed, unsigned int scoreValue)
:DamageableObject(World, imageID, startX, startY, 0, 0.5, 1, hitPoint), m_damageAmt(damageAmt), m_deltaY(deltaY), m_speed(speed), m_flightPlanLength(0), m_scoreValue(scoreValue)
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
    
    // 3.
    /*
     if(the alien has collided with a NachenBlaster-fired projectile or the NachenBlaster ship itself)
     {
         damageCollidingPlayer(m_damageAmt); // TODO: change damagedAmt
     }
     */
    
    // 4.
    if(getY() == VIEW_WIDTH-1 || getY() == 0 || m_flightPlanLength <= 0)
    {
        if(getY() == VIEW_HEIGHT-1)
            setDeltaY(-1.0);
        
        else if (getY() == 0)
            setDeltaY(1.0);
        
        else if (!isSnagglegon() && m_flightPlanLength <= 0)
        {
            int random = randInt(1, 3);
            if (random == 1)
                setDeltaY(0.0);
            else if (random == 2)
                setDeltaY(-1.0);
            else
                setDeltaY(1.0);
        } // Otherwise if the Smallgon or Smoregon’s flight plan length is 0, it will set its travel direction by randomly selecting a new one from these three choices: due left, up and left, or down and left.
        if(!isSnagglegon())
            m_flightPlanLength = randInt(1, 32);
    }
    
    // 5. TODO:
    /*
    if (NachenBlaster::getX() < getX() && NachenBlaster::getY()-4 <= getY() && NachenBlaster::getY()+4 >= getY())
    {
        if(!isSnagglegon() && randInt(1, (20/getWorld()->getLevel())+5) == 1)
        {
            // Turnip* c = new Turnip(this, getX()-14, getY(), 0); // TODO: Fire a turnip toward the NachenBlaster. Hint: When you create a new turnip object in the proper location, give it to your StudentWorld to manage (e.g., animate) along with the other game objects.
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
            return;
        }
     
        doDiffAlienThing();
    }
    */
    
    move();
    m_flightPlanLength--;
    
    // TODO: Finally, after the alien ship has moved itself, it must AGAIN check to see if has collided with the NachenBlaster or a NachenBlaster-fired projectile, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.).
}

void Alien::sufferDamage(double amt, int cause)
{
    // TODO
    /*
    if (an alien collides with a NachenBlaster-fired projectile or vice versa)
    {
        // TODO: 1. The alien ship must be damaged by the projectile as indicated by the projectile (e.g., 2 points of damage from a cabbage, etc.).
        
        if (getHitPt() <= 0)
        {
            getWorld()->increaseScore(m_scoreValue); // Increase the player’s score by 250 points
            setAlive("dead");
            getWorld()->playSound(SOUND_DEATH);
            Explosion* c = new Explosion(this, getX() getY(), 0, 1.0, 0); // TODO: Introduce a new explosion object into the space field
        }
        
        else // if the projectile injured the Smallgon ship but didn’t destroy the ship
            getWorld()->playSound(SOUND_BLAST);
    }
    
    if (an alien collides with the NachenBlaster ship or vice versa)
    {
        NachenBlaster::sufferDamage(m_damageAmt, 0); // TODO: Damage the NachenBlaster appropriately (by causing it to lose 5 hit points) – the NachenBlaster object can then deal with this damage in its own unique way. Hint: The Smallgon object can tell the NachenBlaster that it has been damaged by calling a method the NachenBlaster has (presumably named sufferDamage or something similar).
        setAlive("dead");
        getWorld()->increaseScore(m_scoreValue);
        getWorld()->playSound(SOUND_DEATH);
        Explosion* c = new Explosion(this, getX() getY(), 0, 1.0, 0); // TODO: Introduce a new explosion object into the space field
    }
    */
    possiblyDropGoodie();
}

// Move the player by the current speed in the direction indicated
// by the x and y deltas.
void Alien::move()
{
    moveTo(getX() - 1.0 * m_speed, getY() + m_deltaY * m_speed);
}

// If this alien collided with the player, damage the player and return
// true; otherwise, return false.
bool Alien::damageCollidingPlayer(double amt)
{
    /* TODO:
    if(this alien collided with the player)
    {
        NachenBlaster::sufferDamage(m_damageAmt, 0);
        return true;
    }
     */
    return false;
}

// If this alien drops goodies, drop one with the appropriate probability.
void Alien::possiblyDropGoodie()
{
    /* TODO:
    if(isSmoregon() && randInt(1, 3) == 1)
    {
        if(randInt(1, 2) == 1)
            RGoodie* r = new RGoodie(this, IID_REPAIR_GOODIE, Smoregon::getX(), Smoregon::getY());
        else
            FTGoodie* r = new FTGoodie(this, IID_TORPEDO_GOODIE, Smoregon::getX(), Smoregon::getY());
    } // If a Snoregon decides to drop a goodie, there is a 50% chance that it will be a Repair Goodie, and a 50% chance that it will be a Flatulence Torpedo Goodie. The goodie must be added to the space field at the same x,y coordinates as the destroyed ship.
    
    if(isSnagglegon() && randInt(1, 6) == 1)
    {
        ELGoodie* r = new ELGoodie(this, IID_LIFE_GOODIE, Snagglegon::getX(), Snagglegon::getY());
    }// There is a 1/6 chance that the destroyed Snagglegon ship will drop an Extra Life goodie. The goodie must be added to the space field at the same x,y coordinates as the destroyed ship.
     */
}

//////////////
// Smallgon //
//////////////

Smallgon::Smallgon(StudentWorld* World, double startX, double startY)
:Alien(World, IID_SMALLGON, startX, startY, (5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), 5.0, -1.0, 0.0, 2.0, 250)
//TODO :Alien(World, IID_SMALLGON, startX, startY, (5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), damageAmt, deltaX, deltaY, 2.0, scoreValue)
{}

Smallgon::~Smallgon()
{}

void Smallgon::doDiffAlienThing()
{}

//////////////
// Smoregon //
//////////////

Smoregon::Smoregon(StudentWorld* World, double startX, double startY)
:Alien(World, IID_SMOREGON, startX, startY, (5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), 5.0, -1.0, 0.0, 2.0, 250)
//TODO:Alien(World, IID_SMOREGON, startX, startY, (5.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), damageAmt, deltaX, deltaY, 2.0, scoreValue)
{}

Smoregon::~Smoregon()
{}

bool Smoregon::isSmoregon() const {return false;}

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
:Alien(World, IID_SNAGGLEGON, startX, startY, (10.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), 15.0, -1.0, 0.0, 1.75, 1000)
//TODO:Alien(World, IID_SNAGGLEGON, startX, startY, (10.0*(1.0+(getWorld()->getLevel()-1.0)*0.1)), damageAmt, deltaX, deltaY, 1.75, scoreValue)
{}

Snagglegon::~Snagglegon()
{}

bool Snagglegon::isSnagglegon() const {return false;}

void Snagglegon::doDiffAlienThing()
{
    if(randInt(1, (15/getWorld()->getLevel())+10) == 1)
    {
        // Torpedo* c = new Torpedo(this, getX()-14, getY(), 0); // TODO: Fire a Torpedo toward the NachenBlaster. Hint: When you create a new turnip object in the proper location, give it to your StudentWorld to manage (e.g., animate) along with the other game objects. //
        getWorld()->playSound(SOUND_TORPEDO); //
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

void Projectile::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if (the cabbage/ turnip overlaps with an alien (Smoregon, Smallgon or Snagglegon) ship)
     {
     Alien::attacked();
     // TODO Hint: The cabbage/ turnip can tell the alien object that it has been damaged by calling a method the alien object has (presumably named sufferDamage or something similar).
     
     setAlive("dead");
     return;
     }
     */
    
    doDiffProjectileThing();
    
    /*
     if (the cabbage/ turnip overlaps with an alien (Smoregon, Smallgon or Snagglegon) ship)
     {
     Alien::attacked();
     // TODO Hint: The cabbage/ turnip can tell the alien object that it has been damaged by calling a method the alien object has (presumably named sufferDamage or something similar).
     
     setAlive("dead");
     return;
     }
     */
}

void Projectile::attacked()
{}

Cabbage::Cabbage(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_CABBAGE, startX, startY, 0, 2.0, 0.0, false)
// TODO:Projectile(World, IID_CABBAGE, startX, startY, 0, damageAmt, deltaX, rotates)
{}

Cabbage::~Cabbage(){}

void Cabbage::doDiffProjectileThing()
{
    moveTo(getX()+8, getY());
    setDirection(getDirection()+20);
    // TODO: Check if this is counter-clockwise
}

Turnip::Turnip(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_TURNIP, startX, startY, 0, 2.0, 0.0, false)
// TODO:Projectile(World, IID_TURNIP, startX, startY, 0, damageAmt, deltaX, rotates)
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
// TODO:Projectile(World, IID_TORPEDO, startX, startY, 0, damageAmt, deltaX, rotates)
{}

Torpedo::~Torpedo()
{}

bool Torpedo::isTorpedo() const
{
    return true;
}

void Torpedo::doSomething()
{
    if(isAlive() == false)
        return;
    
    /* TODO:
     if (Flatulence Torpedo must check to see if it has collided with an enemy)
     {
     if (the Flatulence Torpedo was fired by a Snagglegon ship)
     NachenBlaster::attacked();
     else
     Alien::attacked();
     setAlive("dead");
     return;
     }
     
     if (the Flatulence Torpedo was fired by a Snagglegon ship)
     moveTo(getX()-8, getY());
     else
     moveTo(getX()+8, getY());
     
     if (Flatulence Torpedo must check to see if it has collided with an enemy)
     {
     if (the Flatulence Torpedo was fired by a Snagglegon ship)
     NachenBlaster::attacked();
     else
     Alien::attacked();
     setAlive("dead");
     return;
     }
     */
}

PlayerLaunchedTorpedo::PlayerLaunchedTorpedo(StudentWorld* World, double startX, double startY)
:Torpedo(World, startX, startY, 0, 0)
{}

void PlayerLaunchedTorpedo::doSomething()
{
    // TODO
}

AlienLaunchedTorpedo::AlienLaunchedTorpedo(StudentWorld* World, double startX, double startY)
:Torpedo(World, startX, startY, 180, 0)
{}

void AlienLaunchedTorpedo::doSomething()
{
    // TODO
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
    
    /* TODO:
     if(if the NachenBlaster collides with a Goodie)
     {
     inform the StudentWorld object that the user is to receive 100 more points;
     setAlive("dead");
     getWorld()->playSound(SOUND_GOODIE);
     doDiffGoodieThing();
     return;
     }
     
     moveTo(getX()-0.75, getY()-0.75);
     
     if(if the NachenBlaster collides with a Goodie)
     {
     inform the StudentWorld object that the user is to receive 100 more points;
     setAlive("dead");
     getWorld()->playSound(SOUND_GOODIE);
     doDiffGoodieThing();
     return;
     }
     */
}

void Goodie::attacked()
{}

ELGoodie::ELGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_LIFE_GOODIE, startX, startY)
{}

ELGoodie::~ELGoodie()
{}

void ELGoodie::doDiffGoodieThing()
{
    // TODO: Inform the StudentWorld object that the NachenBlaster is to gain one extra life.
}

RGoodie::RGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_REPAIR_GOODIE, startX, startY)
{}

RGoodie::~RGoodie()
{}

void RGoodie::doDiffGoodieThing()
{
    /*
    StudentWorld World;
    NachenBlaster n(World);
    n.getHitPt();
    
    NachenBlaster* nb = new NachenBlaster(this);
    if(n.getHitPt() <= 40)
        n.incHitPt(10);
    else
        NachenBlaster::incHitPt(NachenBlaster::getHitPt()-NachenBlaster::getHitPt()+50);
    */
     // TODO: inform the NachenBlaster object that it just got 10 additional hit points (any additional hit points must NOT cause the NachenBlaster to exceed 50 hit points).
}

FTGoodie::FTGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_TORPEDO_GOODIE, startX, startY)
{}

FTGoodie::~FTGoodie()
{}

void FTGoodie::doDiffGoodieThing()
{
    // TODO: inform the NachenBlaster object that it just received 5 Flatulence Torpedoes. There is no maximum number of torpedoes that the NachenBlaster may have.
}
