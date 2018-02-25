#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_isAlive(true), m_world(World)//, m_control(Control)
{} // page 22

Actor::~Actor()
{
    // delete getWorld(); // wrong!!!! Delete all the memories that only this class made. Or C++ will try to delete it twice. Bad pointer execution
}

bool Actor::isInBound(int x, int y)
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

double Actor::euclidian_dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

StudentWorld* Actor::getWorld()
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

NachenBlaster::NachenBlaster(StudentWorld* World)
 :Actor(World, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0), m_hitPt(50), m_cabbagePt(30), m_torpedoPt(0)
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
                        // TODO:
                        //Cabbage* c = new Cabbage(this, getX()+12, getY());
                        //playSound(SOUND_PLAYER_SHOOT);
                        setCabbagePt(getCabbagePt() - 5);
                    } break;
                    // TODO Hint: When you create a new cabbage object in the proper location, give it to the StudentWorld to manage (e.g., animate) along with the other game objects.
                    
                case KEY_PRESS_TAB:
                    if(getTorpedoPt() > 0)
                    {
                        // TODO:
                        //Torpedo* c = new Torpedo(this, getX()+12, getY(), 0);
                        //playSound(SOUND_TORPEDO);
                        setTorpedoPt(getTorpedoPt() - 1);
                    } break;
                    
                case KEY_PRESS_LEFT:   if(isInBound(x-6, y)) moveTo(x-6, y); break;
                case KEY_PRESS_RIGHT:  if(isInBound(x+6, y)) moveTo(x+6, y); break;
                case KEY_PRESS_DOWN:   if(isInBound(x, y-6)) moveTo(x, y-6); break;
                case KEY_PRESS_UP:     if(isInBound(x, y+6)) moveTo(x, y+6); break;
                    // TODO: Of course, any movement may cause a collision with an alien ship or projectile, so you must check for this.
                    
                    // TODO: case KEY_PRESS_ESCAPE: ; break;
                    
                default:
                    break;
            }
        }
    }
    if (getCabbagePt() < 30)
        setCabbagePt(getCabbagePt() + 1);
}

void NachenBlaster::attacked()
{
    /* TODO:
    if (a projectile like a turnip collides with the NachenBlaster, or vice versa)
    {
        setHitpt(getHitPt() - 2);
        playSound(SOUND_BLAST);
    }
    if (a Flatulence Torpedo collides with the NachenBlaster, or vice versa)
    {
        setHitpt(getHitPt() - 8);
        playSound(SOUND_BLAST);
    }
    
    if (an alien ship collides with the NachenBlaster or vice versa)
        the NachenBlaster incurs damage and the alien ship will be destroyed
        playSound(SOUND_DEATH);
     */
    
    if(getHitPt() <= 0)
        setAlive("dead");
}

void NachenBlaster::setHitPt(int newHitPt){m_hitPt = newHitPt;}
int NachenBlaster::getHitPt() const {return m_hitPt;}

void NachenBlaster::setCabbagePt(int newCabbagePt){m_cabbagePt = newCabbagePt;}
int NachenBlaster::getCabbagePt() const {return m_cabbagePt;}

void NachenBlaster::setTorpedoPt(int newTorpedoPt){m_torpedoPt = newTorpedoPt;}
int NachenBlaster::getTorpedoPt() const {return m_torpedoPt;}

Explosion::Explosion(StudentWorld* World, double startX, double startY, double size)
 :Actor(World, IID_EXPLOSION, startX, startY, 0, size, 0)
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

////////////////
// Projectile //
////////////////

Projectile::Projectile(StudentWorld* World, int imageID, double startX, double startY, int dir)
:Actor(World, imageID, startX, startY, dir, 0.5, 1)
{}

Projectile::~Projectile()
{}

Cabbage::Cabbage(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_CABBAGE, startX, startY, 0)
{}

Cabbage::~Cabbage(){}

void Cabbage::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if()
     {
     step 3: Otherwise, the cabbage must check to see if it has collided with an alien (see the Euclidian distance check on page 10 of this document). If the cabbage overlaps with an alien (Smoregon, Smallgon or Snagglegon) ship:

     • Damage the victim ship appropriately (by causing the object to lose 2 hit points); the damaged object can then deal with this damage in its own unique way (this may result in the damaged object dying/disappearing, a sound effect being played, the user possibly getting points, etc.) Hint: The cabbage can tell the alien object that it has been damaged by calling a method the alien object has (presumably named sufferDamage or something similar).
     
        setAlive("dead");
        return;
     }
     */
    moveTo(getX()+8, getY());
    setDirection(getDirection()+20); // TODO: Check if this is counter-clockwise
    // Finally, after the cabbage has moved itself, the cabbage must AGAIN check to see if has collided with an alien ship, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.), but does not move any further during this tick.
}

Turnip::Turnip(StudentWorld* World, double startX, double startY)
:Projectile(World, IID_TURNIP, startX, startY, 0)
{}

Turnip::~Turnip()
{}

void Turnip::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if()
     {
     step 3: Otherwise, the turnip must check to see if it has collided with the NachenBlaster (see the Euclidian distance check on page 10 of this document). If the turnip overlaps with the NachenBlaster ship:
     
     • Damage the NachenBlaster appropriately (by causing the object to lose 2 hit
     points); the damaged object can then deal with this damage in its own unique way (this may result in the damaged object dying/disappearing, a sound effect being played, the user possibly getting points, etc.) Hint: The turnip can tell the NachenBlaster that it has been damaged by calling a method the NachenBlaster has (presumably named sufferDamage or something similar).
     
     setAlive("dead");
     return;
     }
     */
    moveTo(getX()-6, getY());
    setDirection(getDirection()+20); // TODO: Check if this is counter-clockwise
    // Finally, after the turnip has moved itself, the turnip must AGAIN check to see if has collided with the NachenBlaster, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.), but does not move any further during this tick.
}

Torpedo::Torpedo(StudentWorld* World, double startX, double startY, int dir)
:Projectile(World, IID_TORPEDO, startX, startY, dir)
{} // TODO: A Flatulence Torpedo has a direction of either 0 degrees (if it was fired by the NachenBlaster) or 180 degrees (if it was fired by a Snagglegon).

Torpedo::~Torpedo()
{}

void Torpedo::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     if()
     {
     step 3: Otherwise, the Flatulence Torpedo must check to see if it has collided with an enemy. If the Flatulence Torpedo was fired by a Snagglegon ship, then its only enemy is the NachenBlaster. Otherwise, if the Flatulence Torpedo was fired by the NachenBlaster then its enemy is any alien ship. See the Euclidian distance check on page 10 of this document to determine how to check for collisions. If the Flatulence Torpedo collides with an enemy ship:
     
     • Damage the enemy appropriately (by causing the object to lose 8 hit points); the damaged object can then deal with this damage in its own unique way (this may result in the damaged object dying/disappearing, a sound effect being played, the user possibly getting points, etc.) Hint: The Flatulence Torpedo can tell the enemy object that it has been damaged by calling a method the enemy object has (presumably named sufferDamage or something similar).
     
     setAlive("dead");
     return;
     }
     */
    moveTo(getX()-6, getY()); // TODO: The Flatulence Torpedo must move itself 8 pixels to the left (if it was fired by a Snagglegon) or 8 pixels to the right (if it was fired by the NachenBlaster).
    // Finally, after the Flatulence Torpedo has moved itself, the Flatulence Torpedo must AGAIN check to see if has collided with an enemy, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.), but does not move any further during this tick.
}

////////////
// Goodie //
////////////

Goodie::Goodie(StudentWorld* World, int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(World, imageID, startX, startY, 0, 0.5, 1)
{}

Goodie::~Goodie()
{}

void Goodie::doSomething()
{}

ELGoodie::ELGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_LIFE_GOODIE, startX, startY, 0, 0.5, 1)
{}

ELGoodie::~ELGoodie()
{}

void ELGoodie::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     3.
     if(if the NachenBlaster collides with a Extra Life Goodie)
     {
        a. Inform the StudentWorld object that the user is to receive 100 more points.
     
        setAlive("dead");
        playSound(SOUND_GOODIE);
     
        d. Inform the StudentWorld object that the NachenBlaster is to gain one extra
     life.
     
        return;
     }
     */
    moveTo(getX()-0.75, getY()-0.75);
    
    // TODO: The Extra Life Goodie must then again check to see if it collided with the NachenBlaster, and if so, perform the steps outlined in item #3 above.
}

RGoodie::RGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_REPAIR_GOODIE, startX, startY, 0, 0.5, 1)
{}

RGoodie::~RGoodie()
{}

void RGoodie::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     3.
     if(if the NachenBlaster collides with a Repair Goodie)
     {
     a. Inform the StudentWorld object that the user is to receive 100 more points.
     
     setAlive("dead");
     playSound(SOUND_GOODIE);
     
     d. Inform the NachenBlaster object that it just got 10 additional hit points (any
     additional hit points must NOT cause the NachenBlaster to exceed 50 hit
     points).
     
     return;
     }
     */
    moveTo(getX()-0.75, getY()-0.75);
    
    // TODO: The Repair Goodie must then again check to see if it collided with the NachenBlaster, and if so, perform the steps outlined in item #3 above.
}

FTGoodie::FTGoodie(StudentWorld* World, int imageID, double startX, double startY)
:Goodie(World, IID_TORPEDO_GOODIE, startX, startY, 0, 0.5, 1)
{}

FTGoodie::~FTGoodie()
{}

void FTGoodie::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
     3.
     if(if the NachenBlaster collides with a Flatulence Torpedo Goodie)
     {
     a. Inform the StudentWorld object that the user is to receive 100 more points.
     
     setAlive("dead");
     playSound(SOUND_GOODIE);
     
     d. Inform the NachenBlaster object that it just received 5 Flatulence Torpedoes.
     There is no maximum number of torpedoes that the NachenBlaster may have.
     
     return;
     }
     */
    moveTo(getX()-0.75, getY()-0.75);
    
    // TODO: The Flatulence Torpedo Goodie must then again check to see if it collided with the NachenBlaster, and if so, perform the steps outlined in item #3 above.
}

///////////
// Alien //
///////////

Alien::Alien(StudentWorld* World, int level, int imageID, double startX, double startY, int dir, double size, int depth, int hitPoint, int flightLength, double speed)
:Actor(World, imageID, startX, startY, 0, 0.5, 1), m_hitpoints(hitPoint), m_flightlength(flightLength), m_speed(speed), m_level(level)
{}

Alien::~Alien()
{}

//////////////
// Smallgon //
//////////////

Smallgon::Smallgon(StudentWorld* World, int level, int imageID, double startX, double startY, int hitPoint, int flightLength, double speed)
:Alien(World, level, IID_SMALLGON, startX, startY, 0, 1.5, 1, (5*(1+(level-1)*0.1)), 0, 2.0)
{}

Smallgon::~Smallgon()
{}

void Smallgon::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
    3.
    if(if the Smallgon has collided with a NachenBlaster-fired projectile or the NachenBlaster ship itself)
    {
        attacked();
    }
    
    4.
    if (The Smallgon will check to see if it needs a new flight plan because the current flight plan length has reached zero OR the Smallgon has reached the top or bottom of the screen due to its current flight plan. If either condition is true, the Smallgon will use the following approach to select a new flight plan)
    {
        a. If the Smallgon’s y coordinate is greater than or equal to VIEW_HEIGHT-1, then the Smallgon will set its travel direction to down and left.
        b. Otherwise, if the Smallgon’s y coordinate is less than or equal to 0, then the Smallgon will set its travel direction to up and left.
        c. Otherwise if the Smallgon’s flight plan length is 0, the Smallgon will set its travel direction by randomly selecting a new one from these three choices: due left, up and left, or down and left.
        d. The Smallgon will pick a random new flight plan length in the range [1, 32].
     
    }
     
    5.
    if (the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y coordinate that is within [-4,4] pixels of the NachenBlaster’s y coordinate)
    {
        if (There is a 1 in ((20/CurrentLevelNumber)+5) chance)
        {
            i. Fire a turnip toward the NachenBlaster, adding the new turnip 14 pixels to the left of the center of the Smallgon ship and at the Smallgon’s y coordinate. Hint: When you create a new turnip object in the proper location, give it to your StudentWorld to manage (e.g., animate) along with the other game objects.
            playSound(SOUND_ALIEN_SHOOT);
            return;
        }
    }
     
    The Smallgon will try to move in its current travel direction (as determined by the last flight plan);
    reduce its flight plan length by 1;
    If its travel direction is:
    a. Up and left: It must move N pixels up and N pixels left using the moveTo() method, where N is the current travel speed.
    b. Down and left: It must move N pixels down and N pixels left using the moveTo() method, where N is the current travel speed.
    c. Due left: It must move N pixels left using the moveTo() method, where N is the current travel speed.
    

    Finally, after the Smallgon ship has moved itself, it must AGAIN check to see if has collided with the NachenBlaster or a NachenBlaster-fired projectile, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.).
    */
}

void Smallgon::attacked()
{
    /*
    if (a Smallgon collides with a NachenBlaster-fired projectile or vice versa)
    {
        1. The Smallgon ship must be damaged by the projectile as indicated by the projectile (e.g., 2 points of damage from a cabbage, etc.).
        if (the collision results in the Smallgon’s hit points reaching zero or below)
        {
            Increase the player’s score by 250 points;
            setAlive("dead");
            getControl()->playSound(SOUND_DEATH);
            d. Introduce a new explosion object into the space field at the same x,y location as the Smallgon.
        }
        
        else if (the projectile injured the Smallgon ship but didn’t destroy the ship)
            playSound(SOUND_BLAST);
    }
    
    if (a Smallgon collides with the NachenBlaster ship or vice versa)
    {
        1. Damage the NachenBlaster appropriately (by causing it to lose 5 hit points) – the NachenBlaster object can then deal with this damage in its own unique way. Hint: The Smallgon object can tell the NachenBlaster that it has been damaged by calling a method the NachenBlaster has (presumably named sufferDamage or something similar).
        setAlive("dead");
        3. Increase the player’s score by 250 points.
        playSound(SOUND_DEATH);
        5. Introduce a new explosion object into the space field at the same x,y coordinates as the Smallgon (see the Explosion section for more details)
    }
     */
}

//////////////
// Smoregon //
//////////////

Smoregon::Smoregon(StudentWorld* World, int level, int imageID, double startX, double startY, int hitPoint, int flightLength, double speed)
:Alien(World, level, IID_SMOREGON, startX, startY, 0, 1.5, 1, (5*(1+(level-1)*0.1)), 0, 2.0)
{}

Smoregon::~Smoregon()
{}

void Smoregon::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
    3.
    if(if the Smallgon has collided with a NachenBlaster-fired projectile or the NachenBlaster ship itself)
    {
        attacked();
    }
    
    4. // whole 4. section same as Smallgon's
    if (The Smallgon will check to see if it needs a new flight plan because the current flight plan length has reached zero OR the Smallgon has reached the top or bottom of the screen due to its current flight plan. If either condition is true, the Smallgon will use the following approach to select a new flight plan)
    {
        a. If the Smallgon’s y coordinate is greater than or equal to VIEW_HEIGHT-1, then the Smallgon will set its travel direction to down and left.
        b. Otherwise, if the Smallgon’s y coordinate is less than or equal to 0, then the Smallgon will set its travel direction to up and left.
        c. Otherwise if the Smallgon’s flight plan length is 0, the Smallgon will set its travel direction by randomly selecting a new one from these three choices: due left, up and left, or down and left.
        d. The Smallgon will pick a random new flight plan length in the range [1, 32].
                
    }
    
    5.
    if (the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y coordinate that is within [-4,4] pixels of the NachenBlaster’s y coordinate)
    {
        a. // 5.a. is the same as Smallgon's
        if (There is a 1 in ((20/CurrentLevelNumber)+5) chance)
        {
            i. Fire a turnip toward the NachenBlaster, adding the new turnip 14 pixels to the left of the center of the Smallgon ship and at the Smallgon’s y coordinate. Hint: When you create a new turnip object in the proper location, give it to your StudentWorld to manage (e.g., animate) along with the other game objects.
            playSound(SOUND_ALIEN_SHOOT);
            return;
        }
        b.
        There is a 1 in ((20/CurrentLevelNumber)+5) chance during this tick that the Smoregon will change its flight plan:
        i. It will set its travel direction to due left.
        ii. It will set the length of its flight plan to VIEW_WIDTH steps.
        iii. It will set its travel speed to 5 pixels per tick: Ramming speed!.
        iv. Continue on with the next step.
    }
    
    6. // same as Smallgon's
    The Smallgon will try to move in its current travel direction (as determined by the last flight plan);
    reduce its flight plan length by 1;
    If its travel direction is:
    a. Up and left: It must move N pixels up and N pixels left using the moveTo() method, where N is the current travel speed.
    b. Down and left: It must move N pixels down and N pixels left using the moveTo() method, where N is the current travel speed.
    c. Due left: It must move N pixels left using the moveTo() method, where N is the current travel speed.
    
    
    Finally, after the Smallgon ship has moved itself, it must AGAIN check to see if has collided with the NachenBlaster or a NachenBlaster-fired projectile, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.).
        */
}

void Smoregon::attacked()
{
    /*
    // for this whole attacked function, only 1.e. is an addition from Smallgon's
    if (a Smallgon collides with a NachenBlaster-fired projectile or vice versa)
    {
        1. The Smallgon ship must be damaged by the projectile as indicated by the projectile (e.g., 2 points of damage from a cabbage, etc.).
        if (the collision results in the Smallgon’s hit points reaching zero or below)
        {
            Increase the player’s score by 250 points;
            setAlive("dead");
            getControl()->playSound(SOUND_DEATH);
            d. Introduce a new explosion object into the space field at the same x,y location as the Smallgon.
        }
        
        else if (the projectile injured the Smallgon ship but didn’t destroy the ship)
            playSound(SOUND_BLAST);
    }
    
    if (a Smallgon collides with the NachenBlaster ship or vice versa)
    {
        1. Damage the NachenBlaster appropriately (by causing it to lose 5 hit points) – the NachenBlaster object can then deal with this damage in its own unique way. Hint: The Smallgon object can tell the NachenBlaster that it has been damaged by calling a method the NachenBlaster has (presumably named sufferDamage or something similar).
        setAlive("dead");
        3. Increase the player’s score by 250 points.
        playSound(SOUND_DEATH);
        5. Introduce a new explosion object into the space field at the same x,y coordinates as the Smallgon (see the Explosion section for more details)
    }
    
    // addition starts
    1.e. There is a 1/3 chance that the destroyed Smoregon ship will drop a goodie.
    If it decides to drop a goodie, there is a 50% chance that it will be a Repair Goodie, and a 50% chance that it will be a Flatulence Torpedo Goodie. The goodie must be added to the space field at the same x,y coordinates as the destroyed ship.
    // addition ends
     */
}

////////////////
// Snagglegon //
////////////////

Snagglegon::Snagglegon(StudentWorld* World, int level, int imageID, double startX, double startY, int hitPoint, int flightLength, double speed)
:Alien(World, level, IID_SNAGGLEGON, startX, startY, 0, 1.5, 1, (10*(1+(level-1)*0.1)), 0, 1.75)
{}

Snagglegon::~Snagglegon()
{}

void Snagglegon::doSomething()
{
    if(isAlive() == false)
        return;
    
    /*
    3.
    if(if the Smallgon has collided with a NachenBlaster-fired projectile or the NachenBlaster ship itself)
    {
        attacked();
    }
    
    4. // whole 4. section same as Smallgon's
    if (The Smallgon will check to see if it needs a new flight plan because the current flight plan length has reached zero OR the Smallgon has reached the top or bottom of the screen due to its current flight plan. If either condition is true, the Smallgon will use the following approach to select a new flight plan)
    {
        a. If the Smallgon’s y coordinate is greater than or equal to VIEW_HEIGHT-1, then the Smallgon will set its travel direction to down and left.
        b. Otherwise, if the Smallgon’s y coordinate is less than or equal to 0, then the Smallgon will set its travel direction to up and left.
            
        // Snagglegon doesn't have 4.c or 4.d.
        c. Otherwise if the Smallgon’s flight plan length is 0, the Smallgon will set its travel direction by randomly selecting a new one from these three choices: due left, up and left, or down and left.
        d. The Smallgon will pick a random new flight plan length in the range [1, 32].
        // Snagglegon doesn't have 4.c or 4.d.
    }
    
    5.
    if (the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y coordinate that is within [-4,4] pixels of the NachenBlaster’s y coordinate)
    {
        a. // 5.a. is the similar to Smallgon's/ Smoregon's, besides the probability, torpedo instead of turnip, and playsound of torpedo
        if (There is a 1 in ((15/CurrentLevelNumber)+10) chance)
        {
            i. Fire a torpedo toward the NachenBlaster, adding the new torpedo 14 pixels to the left of the center of the Smallgon ship and at the Smallgon’s y coordinate. Hint: When you create a new torpedo object in the proper location, give it to your StudentWorld to manage (e.g., animate) along with the other game objects.
            playSound(SOUND_TORPEDO);
            return;
        }
    }
    
    6. // same as Smallgon's
    The Smallgon will try to move in its current travel direction.
    If its travel direction is:
    a. Up and left: It must move N pixels up and N pixels left using the moveTo() method, where N is the current travel speed.
    b. Down and left: It must move N pixels down and N pixels left using the moveTo() method, where N is the current travel speed.
    // Snagglegon doesn't have 6.c.
    c. Due left: It must move N pixels left using the moveTo() method, where N is the current travel speed.
    // Snagglegon doesn't have 6.c.
    
    Finally, after the Smallgon ship has moved itself, it must AGAIN check to see if has collided with the NachenBlaster or a NachenBlaster-fired projectile, using the same algorithm described in step #3 above. If so, it must perform the same behavior as described in step #3 (e.g., damage the object, etc.).
        */
}

void Snagglegon::attacked()
{
    /*
    // for this whole attacked function, only 1.e. is an addition from Smallgon's
    if (a Smallgon collides with a NachenBlaster-fired projectile or vice versa)
    {
        1. The Smallgon ship must be damaged by the projectile as indicated by the projectile (e.g., 2 points of damage from a cabbage, etc.).
        if (the collision results in the Smallgon’s hit points reaching zero or below)
        {
            Increase the player’s score by 1000 points; // was 250
            setAlive("dead");
            getControl()->playSound(SOUND_DEATH);
            d. Introduce a new explosion object into the space field at the same x,y location as the Smallgon.
        }
        
        else if (the projectile injured the Smallgon ship but didn’t destroy the ship)
            playSound(SOUND_BLAST);
    }
    
    if (a Smallgon collides with the NachenBlaster ship or vice versa)
    {
        1. Damage the NachenBlaster appropriately (by causing it to lose 15 hit points) – the NachenBlaster object can then deal with this damage in its own unique way. Hint: The Smallgon object can tell the NachenBlaster that it has been damaged by calling a method the NachenBlaster has (presumably named sufferDamage or something similar). // was 5 hit points, instead of 15
        setAlive("dead");
        3. Increase the player’s score by 1000 points. // was 250 instead of 1000
        playSound(SOUND_DEATH);
        5. Introduce a new explosion object into the space field at the same x,y coordinates as the Smallgon (see the Explosion section for more details)
    }
    
    // addition starts
    There is a 1/6 chance that the destroyed Snagglegon ship will drop an Extra Life goodie. The goodie must be added to the space field at the same x,y coordinates as the destroyed ship.
    // addition ends
     */
}
