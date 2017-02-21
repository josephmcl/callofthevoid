//fighter.cpp

#include "header/fighter.hpp"

Fighter::Fighter()
{
    //physical properties
    active = false;
    pos.set(0, 0);
    dir = 0;
    targetVel = 0;
    maxVel = 300;
    accScalar = 20;
    friction = .25;
    
    //combat
    target = nullptr;
    hp = 100;
    sp = 100;
    spRegen = 0;
    blocking = false;
    blockHitCooldown = 0;
    invincible = 0;
    
    //animation
    currentFrame = 0;
    currentMove = MOVE_NONE;
    frameRate = 18;
    next = 1/frameRate;
    stunTimer = 0;
    
    //TODO read from animation scripts
    Script script = Script("dat/knight.txt");
    
    while (!script.done())
    {
        switch(script.getMove())
        {
        case MOVE_NONE:
            stand[script.getDir()] = *script.getFrame();
            break;
        case MOVE_WALK:
            walk[script.getDir()].addFrame(script.getFrame());
            break;
        case MOVE_LIGHT_ATTACK:
            lightAttack[script.getDir()].addFrame(script.getFrame());
            break;
        case MOVE_ROLL:
            roll[script.getDir()].addFrame(script.getFrame());
            break;
        case MOVE_BLOCK:
            shield[script.getDir()] = *script.getFrame();
            break;
        case MOVE_STUN:
            stun[script.getDir()].addFrame(script.getFrame());
            break;
        case MOVE_PRONE:
            prone[script.getDir()].addFrame(script.getFrame());
            break;
        }
        script.next();
    }
}

Fighter::~Fighter()
{
    
}

void Fighter::update(Timer* timer)
{
    //get timer data
    float delta = timer->getDelta();
    
    //decrement stun timer
    if (stunTimer > 0)
        stunTimer -= delta;
    
    //decrement invincibility timer
    if (invincible > 0)
        invincible -= delta;
    
    //animation
    if (currentMove != MOVE_NONE) //standing still = no animation (for now)
    {
        if (next < 0) //time for next frame
        {
            next = 1/frameRate;         //reset countdown
            currentFrame++;             //increment frame
            
            switch(currentMove) //which animation are we in? do we need to loop it or end it?
            {
            case MOVE_WALK:
                if (currentFrame >= walk[dir].size())
                {
                    cout << walk[dir].size() << endl;
                    currentFrame = 0;
                }
                break;
            case MOVE_LIGHT_ATTACK:
                if (currentFrame >= lightAttack[dir].size())
                {
                    currentMove = MOVE_NONE;
                }
                break;
            case MOVE_ROLL:
                if (currentFrame >= roll[dir].size())
                {
                    currentMove = MOVE_NONE;
                }
                break;
            case MOVE_STUN:
                if (currentFrame >= stun[dir].size())
                {
                    if (stunTimer <= 0)
                    {
                        currentMove = MOVE_NONE;
                    } else {
                        currentFrame = 0;
                    }
                }
                break;
            case MOVE_PRONE:
                if (currentFrame >= prone[dir].size())
                {
                    if (stunTimer <= 0)
                    {
                        currentMove = MOVE_NONE;
                    } else {
                        currentFrame = 0;
                    }
                }
                break;
            }
            
        } else { //keep counting down
            next -= delta;
        }
    }
    
    //apply acceleration to velocity
    vel.addX(acc.getX() * delta);
    vel.addY(acc.getY() * delta);
    
    //cap velocity
    if (vel.magnitude() > maxVel)
        vel.resize(maxVel);
    
    //save old position for correction (bugs, lag, etc.)
    posOld = pos;
    
    //apply velocity to position
    pos.addX(vel.getX() * delta);
    pos.addY(vel.getY() * delta);
    
    //will the player leave the boundaries?
    if ((pos.getX() + vel.getX() * delta < 0)
    ||  (pos.getX() + vel.getX() * delta > SCREEN_WIDTH/PIXEL_RATIO - frame.getPos().w))
    {
        vel.setX(0); //stop moving in the x axis
        revertXPos();
    }
    
    if ((pos.getY() + vel.getY() * delta < UI_HEIGHT)
    ||  (pos.getY() + vel.getY() * delta > SCREEN_HEIGHT/PIXEL_RATIO - frame.getPos().h))
    {
        vel.setY(0); //stop moving in the x axis
        revertYPos();
    }
    
    //check if we're walking and set current move appropriately
    if ((acc.getX() > 0) || (acc.getY() > 0))
        if (currentMove == MOVE_NONE)
            currentMove = MOVE_WALK;
    if ((acc.getX() == 0) && (acc.getY() == 0))
        if (currentMove == MOVE_WALK)
            currentMove = MOVE_NONE;
    
    //apply friction to velocity
    vel.addX(-vel.getX() * friction);
    vel.addY(-vel.getY() * friction);
    
    //regenerate SP
    if (!blocking)
    {
        if (spRegen < 0)
        {
            spRegen = .013;
            if (sp < 100)
                sp++;
        } else {
            spRegen -= delta;
        }
    }
    
    //decrement block hit cooldown
    if (blockHitCooldown > 0)
        blockHitCooldown -= delta;
}

Frame* Fighter::getFrame()
{
    if (active) //is the figher alive/in play?
    {
        //calculate direction
        if (target == nullptr) //no target
        {
            face = acc;
        } else {
            if (!target->getActive())
            {
                target = nullptr;
                face = acc;
            } else {
                face.setX(target->getPos().getX() - pos.getX());
                face.setY(target->getPos().getY() - pos.getY());
            }
        }
        if ((face.getX() != 0) || (face.getY() != 0))
        {
            float a = face.angle();
            if (face.getX() > 0)
            {
                if (a < -30)
                {
                    dir = NORTHEAST;
                } else if (a > 30)
                {
                    dir = SOUTHEAST;
                } else {
                    dir = EAST;
                }
            } else if (face.getX() < 0) {
                if (a < -30)
                {
                    dir = SOUTHWEST;
                } else if (a > 30)
                {
                    dir = NORTHWEST;
                } else {
                    dir = WEST;
                }
            } else { //because of the dead zone
                if (face.getY() > 0)
                {
                    dir = SOUTHWEST;
                } else {
                    dir = NORTHEAST;
                }
            }
        }
        
        //return a frame (based on the current move and direction)
        switch(currentMove)
        {
        default:                    //standing
        case MOVE_NONE:
            updateFrameWithPosition(&stand[dir]);
            break;
        case MOVE_WALK:             //walking
            updateFrameWithPosition(walk[dir].getFrame(currentFrame));
            break;
        case MOVE_LIGHT_ATTACK:     //light attack
            updateFrameWithPosition(lightAttack[dir].getFrame(currentFrame));
            break;
        case MOVE_ROLL:             //roll
            updateFrameWithPosition(roll[dir].getFrame(currentFrame));
            break;
        case MOVE_STUN:             //stun
            updateFrameWithPosition(stun[dir].getFrame(currentFrame));
            break;
        case MOVE_PRONE:             //prone
            updateFrameWithPosition(prone[dir].getFrame(currentFrame));
            break;
        }
    }
        
    return &frame;
}

Frame* Fighter::getShieldFrame()
{
    if (blocking)
    {
        shieldFrame = shield[dir];
        shieldFrame.setPos(pos.getX() + shield[dir].getX(), pos.getY() + shield[dir].getY());
        return &shieldFrame;
    } else {
        return nullptr;
    }
}


int Fighter::getDir() { return dir; }

bool Fighter::getActive() { return active; }

Point Fighter::getPos() { return pos; }

int Fighter::getHP() { return hp; }

int Fighter::getSP() { return sp; }

void Fighter::setActive(bool a) { active = a; }

void Fighter::setPos(int a, int b)
{
    pos.setX(a);
    pos.setY(b);
}

void Fighter::updateFrameWithPosition(Frame* f)
{
    frame = *f;
    frame.setPos(pos.getX() + f->getX(), pos.getY() + f->getY());
}

void Fighter::setAcc(float x, float y)
{
    if ((currentMove == MOVE_NONE) || (currentMove == MOVE_WALK))
    {
        //scale input values to max acceleration
        x = x * accScalar;
        y = y * accScalar;
        
        //set acceleration
        acc.setX(x);
        acc.setY(y);
    }
}

void Fighter::setAccX(float x)
{
    if ((currentMove == MOVE_NONE) || (currentMove == MOVE_WALK))
    {
        //scale input values to max acceleration
        x = x * accScalar;
        
        //set acceleration
        acc.setX(x);
    }
}

void Fighter::setAccY(float y)
{
    if ((currentMove == MOVE_NONE) || (currentMove == MOVE_WALK))
    {
        //scale input values to max acceleration
        y = y * accScalar;
        
        //set acceleration
        acc.setY(y);
    }
}

Frame* Fighter::getFrameOldX()
{
    getFrame();
    frame.setX(posOld.getX());
    return &frame;
}

Frame* Fighter::getFrameOldY()
{
    getFrame();
    frame.setY(posOld.getY());
    return &frame;
}

void Fighter::revertXPos() { pos.setX(posOld.getX()); }

void Fighter::revertYPos() { pos.setY(posOld.getY()); }

void Fighter::revertPos()
{
    revertXPos();
    revertYPos();
}

bool Fighter::doMove(int m)
{
    

    if ((currentMove == MOVE_NONE) || (currentMove == MOVE_WALK))
    {
        switch(m)
        {
            case MOVE_ROLL:
                if (sp > 30)
                {
                    sp -= 35;
                    spRegen = .6;
                    acc.resize(2000);
                    vel.resize(100000);
                } else {
                    m = -1;
                }
                break;
            case MOVE_LIGHT_ATTACK:
                if (sp > 15)
                {
                    sp -= 20;
                    spRegen = .6;
                    acc.set(0,0);
                } else {
                    m = -1;
                }
                break;
            case MOVE_STUN:
                vel.set(0,0);
                acc.set(0,0);
                break;
            case MOVE_PRONE:
                vel.set(0,0);
                acc.set(0,0);
                break;
        }
        
        //if we can do the move...
        if (m != -1)
        {
            currentMove = m;        //set current move
            currentFrame = 0;       //reset frame counter
            blocking = false;       //stop blocking
            return true;            //report that the move succeeded
        }
    }
    return false;   //report that the move failed to execute
}

bool Fighter::blockStart()
{
    if ((blocking == false) && ((currentMove == MOVE_NONE) || (currentMove == MOVE_WALK)))
    {
        blocking = true;
        return true;
    }
    return false;
}

bool Fighter::blockStop()
{
    if (blocking == true)
    {
        blocking = false;
        return true;
    }
    return false;
}

void Fighter::setTarget(Fighter* f) { target = f; }

bool Fighter::getHasTarget()
{
    if (target == nullptr) return false;
    return true;
}

void Fighter::clearTarget() { target = nullptr; }

bool Fighter::hurt(int x, int d)
{
    bool blocked = blocking;
    if (((dir - d <= 1) and (dir - d >= -1)) or (dir - d == 5) or (dir - d == -5))
        blocked = false;
    
    if (blocked) //if it was blocked...
    {
        if (blockHitCooldown <= 0)
        {
            sp -= 75;
            blockHitCooldown = 1;
            if (sp < 0)
            {
                //go prone
                sp = 0;
                stunTimer = 1.6;
                spRegen = 1.6;
                invincible = .3;
                currentMove = MOVE_NONE;
                doMove(MOVE_PRONE);
            }
        }
        return false; //report that the attack was blocked
        
    } else { //successful hit
        //take damage (if not temporarily invincible)
        if (invincible <= 0)
        {
            hp -= x;
        }
        //get stunned (if not already prone)
        if (currentMove != MOVE_PRONE)
        {
            currentMove = MOVE_NONE;
            doMove(MOVE_STUN);
            stunTimer = .6;
        } else {
            invincible = .3;
        }
        //DEATH
        if (hp <= 0)
        {
            active = false;
            frame = Frame(0, 0, 0, 0, 0, 0, 0, 0, 0, SHEET_KNIGHT);
        }
        
        return true; //report that the attack was successful
    }
}