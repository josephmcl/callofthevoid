//eventhandler.hpp

#ifndef _EVENTHANDLER_H
#define _EVENTHANDLER_H

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "timer.hpp"
#include "point.hpp"

using namespace std;

class EventHandler
//keeps track of all user input (keyboard/controller)
//TODO: mouse functionality
//TODO: controller functionality
{
public:
    //constructors and destructors
    EventHandler();
    ~EventHandler();
    
    //public methods
    void update();      //called every frame
    
    //getters
    bool windowClosed();                        //was the window closed?
    bool keyHeld(int k, int t);                 //key key k held for t milliseconds?
    bool keyTapped(int k);                      //was key k tapped?
    bool buttonHeld(int b, int p, int t);       //was button b held for t milliseconds by player p?
    bool buttonTapped(int b, int p);            //was button b tapped by player p?
    float getXAxisLeft(int player);             //left x-axis value for player p
    float getYAxisLeft(int player);             //left y-axis value for player p
    
private:
    //SDL objects
    SDL_Event event;
    SDL_Joystick* controller[4];
    
    //timer
    Timer timer;
    
    //internal methods
    void press(int k);      //flags key as pressed
    void release(int k);    //flags key as unpressed
    
    //keyboard variables
    int keys[20];           //list of current keys held
    float time[20];         //how long the keys have been held
    int taps[5];            //list of recently tapped keys
    
    //joystick variables
    Point leftAxis[4];
    
    //internal variables
    bool quit;
};

#endif