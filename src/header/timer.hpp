 //timer.hpp

#ifndef _TIMER_H
#define _TIMER_H

#include <SDL2/SDL.h>

class Timer
//tick tock
{
public:
    //constructors and destructors
    Timer();
    
    //called every frame to update delta
    void update();
    
    //getters
    float getTime();        //present
    float getDelta();       //delta
    float getFR();          //framerate

private:
    //members
    long past;
    long present;
    float delta;
    float framerate;
};

#endif