//fighter.hpp

#ifndef _FIGHTER_H
#define _FIGHTER_H

#include <iostream>
#include "constants.hpp"
#include "timer.hpp"
#include "point.hpp"
#include "frame.hpp"
#include "script.hpp"
#include "hasframe.hpp"
#include "move.hpp"

class Fighter : public HasFrame
//an object that is displayed on the screen
//keeps track of animation between frames
{
public:
    //constructors and destructors
    Fighter();
    ~Fighter();
    
    //update
    void update(Timer* timer);
    
    //getters
    Frame* getFrame();          //gets a pointer to the current frame
    Frame* getShieldFrame();    //gets a pointer to the shield's frame
    int getDir();         //gets current direction
    bool getActive();           //are we using this fighter?
    Point getPos();             //gets the fighter's coordinates
    int getHP();                //get health points
    int getSP();                //get stamina points
    
    //setters
    void setActive(bool a);
    void setPos(int x, int y);
    void updateFrameWithPosition(Frame* f);
        //updates the current frame's position relative to the fighter's position
    
    //physics
    void setAcc(float x, float y);
    void setAccX(float x);
    void setAccY(float y);
    void applyFriction(float delta);
    Frame* getFrameOldX();  //gets a pointer to the current frame with x position reverted to last position
    Frame* getFrameOldY();  //gets a poiner to the current frame with y position reverted to last position
    void revertXPos();
    void revertYPos();
    void revertPos();
    
    
    //combat
    bool doMove(int m);             //sets a move UNLESS a move is already active
    bool blockStart();              //start blocking
    bool blockStop();               //stop blocking
    void setTarget(Fighter* f);     //designates a target from the other players
    bool getHasTarget();            //does this fighter have a target?
    void clearTarget();             //removes target designation (if we have one)
    bool hurt(int x, int d);        //fighter loses x health points
                                        //(unless blocked... enemy fighter has direction d)
    
private:
    //physical properties
    bool active;            //is this fighter being used? (if false: out of play, dead, etc.)
    Point pos;              //position
    Point posOld;           //old position (if in illegal position, revert to this)
    Point vel;              //velocity
    Point acc;              //acceleration
    short int dir;          //direction from 0-5, starting at southwest, proceeding counterclockwise
    Point face;             //vector to deterine dir
    float targetVel;        //target velocity for a given degree of joystick tilt
    float maxVel;           //maximum velocity (joystick at full tilt)
    float accScalar;        //acceleration scalar
    float friction;         //acceleration reduction
    
    //combat
    Fighter* target;        //pointer to this fighter's target
    int hp;                 //health points (if hp <= 0 then death)
    int sp;                 //stamina points (used for actions)
    float spRegen;          //time until the fighter regain stamina points
    bool blocking;          //is the fighter blocking?
    float blockHitCooldown; //time until we can take sp damage again
    float invincible;       //invibility timer (for prone)
    
    //animation
    int currentFrame;       //which frame of the current animation is showing?
    int currentMove;        //if we're executing a move: which one?
    float frameRate;        //animation speed (can be delayed for individual frames)
    float next;             //counts until next frame
    Frame frame;                    //pointer to current frame
    Frame shieldFrame;              //pointer to current shield frame
    Frame shield[6];                //shield frame
    Frame stand[6];                 //standing animation
    Move walk[6];                   //running animation
    Move lightAttack[6];            //light attack animation
    Move roll[6];                   //rolling animation
    Move stun[6];                   //stunned animation
    Move prone[6];                  //prone animation (after shield break)
    float stunTimer;                  //milliseconds of stun time remanining
};



#endif
